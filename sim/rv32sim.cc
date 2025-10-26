// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Simulator class implementation.

#include "sim/rv32sim.hh"

#include <numeric>

#include "base/bit_utils.hh"
#include "sim/config.hh"
#include "sim/elfloader.hh"
#include "sim/instruction.hh"
#include "sim/isa/rv32i/rv32i.hh"
#include "sim/operands.hh"

namespace rv32 {

Simulator::Simulator(const std::vector<std::string>& cmd) {
  auto elf_path = cmd.front();
  loadElf(elf_path);
  createExecutionEnvironment(cmd);
  rv32i::registerInstructions(instructions_registry_);
}

void Simulator::run() {
  IInstruction::ExecutionResult res;

  do {
    RawInstruction raw = state_.mem.get<RawInstruction>(state_.pc);
    const IInstruction* inst = instructions_registry_.get(raw);
    const Operands operands = extractOperands(raw);
    res = inst->execute(state_, operands);
  } while (res != IInstruction::ExecutionResult::kExit);
}

void Simulator::createExecutionEnvironment(
    const std::vector<std::string>& cmd) {
  Word argc = cmd.size();
  Addr sp = config::kStackTop -
            config::kArgMax;  // to leave space to store whole argv strings
  Addr arg_string_addr = sp;
  sp -= (sizeof(Addr) * (argc + 1) +
         sizeof(Word));  // to store argc and argv pointers

  assert(bits::isAligned(sp, config::kStackAlignment));
  state_.rf.set(helpers::underlying(RegisterFile::Register::kSP),
                sp);  // at this point SP will be at program start

  state_.mem.emit(sp, argc);
  sp += sizeof(Word);

  for (const auto& arg : cmd) {
    state_.mem.copy(arg_string_addr, arg.c_str(), arg.size());
    state_.mem.emit(sp, arg_string_addr);
    sp += sizeof(Addr);
    arg_string_addr += arg.size();
  }

  state_.mem.emit(sp, static_cast<Addr>(0));  // argv[argc] = nullptr
}

void Simulator::loadElf(const std::filesystem::path& path) {
  ElfLoader loader(path);
  loader.load(state_.mem);
}
}  // namespace rv32
