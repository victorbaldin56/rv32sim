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
#include "sim/isa/rv32im/rv32im.hh"
#include "sim/isa/rv32imf/rv32imf.hh"
#include "sim/isa/rv32imf_zbb/rv32imf_zbb.hh"
#include "sim/operands.hh"

namespace rv32 {

using namespace std::string_literals;

Simulator::Simulator(const std::vector<std::string>& cmd)
    : logger_(spdlog::get("Simulator")) {
  std::string argv_log_string = std::accumulate(
      cmd.begin(), cmd.end(), "command line: "s,
      [](auto sum, const auto& cur) { return sum + " " + cur; });
  logger_->trace("{}", argv_log_string);

  std::filesystem::path elf_path = cmd.front();
  loadElf(elf_path);
  createExecutionEnvironment(cmd);

  rv32i::registerInstructions(instructions_registry_);
  rv32im::registerInstructions(instructions_registry_);
  rv32imf::registerInstructions(instructions_registry_);
  rv32imf_zbb::registerInstructions(instructions_registry_);

  logger_->info("Starting simulation...");
}

void Simulator::run() {
  while (true) {
    RawInstruction raw = state_.mem.get<RawInstruction>(state_.pc.get());
    const IInstruction* inst = instructions_registry_.get(raw);
    if (inst == nullptr) {
      throw IllegalInstruction(raw, state_.pc.get());
    }

    const Operands operands = extractOperands(raw);
    logger_->trace("PC: 0x{:x}, instruction: {}, {}", state_.pc.get(),
                   inst->getName(), operands.toText());

    ExecutionResult res = inst->execute(state_, operands);
    if (res == ExecutionResult::kOk) {
      continue;
    }
    if (res == ExecutionResult::kExit) {
      break;
    }

    throwException(res);
  }
}

void Simulator::throwException [[noreturn]] (ExecutionResult res) {
  switch (res) {
    case ExecutionResult::kMisalignment:
      throw Exception("Misaligned instruction", state_.pc.get());
    default:
      assert(0 && "Unreachable");
  }
}

void Simulator::createExecutionEnvironment(
    const std::vector<std::string>& cmd) {
  Word argc = cmd.size();
  Addr sp = config::kStackTop -
            config::kArgMax;  // to leave space to store whole argv strings
  Addr arg_string_addr = sp;
  sp -= (sizeof(Addr) * (argc + 1) +
         sizeof(Word));  // to store argc and argv pointers

  sp = bits::alignDown(sp, config::kStackAlignment);
  state_.rf.set(helpers::underlying(RegisterFile::Register::kSP),
                sp);  // at this point SP will be at program start

  state_.mem.emit(sp, argc);
  sp += sizeof(Word);

  std::for_each(cmd.cbegin(), cmd.cend(), [&](const auto& arg) {
    state_.mem.copy(arg_string_addr, arg.c_str(), arg.size());
    state_.mem.emit(sp, arg_string_addr);
    sp += sizeof(Addr);
    arg_string_addr += arg.size();
  });

  state_.mem.emit(sp, static_cast<Addr>(0));  // argv[argc] = nullptr
}

void Simulator::loadElf(const std::filesystem::path& path) {
  ElfLoader loader(path);
  loader.load(state_.mem);
  state_.pc.set(loader.getEntryPC());
}

ExecutionResult SimulatorState::ecall(SimulatorState& state) {
  using enum RegisterFile::Register;

  Word syscall = state.rf.get(kA7);

  switch (static_cast<Syscall>(syscall)) {
    case Syscall::kRead:
      state.rf.set(kA0, state.mem.read(std::bit_cast<int>(state.rf.get(kA0)),
                                       state.rf.get(kA1), state.rf.get(kA2)));
      ++state.pc;
      return ExecutionResult::kOk;
    case Syscall::kWrite:
      state.rf.set(kA0, state.mem.write(std::bit_cast<int>(state.rf.get(kA0)),
                                        state.rf.get(kA1), state.rf.get(kA2)));
      ++state.pc;
      return ExecutionResult::kOk;
    case Syscall::kExit:
      return ExecutionResult::kExit;
    default:
      throw Simulator::Exception(
          std::format("Unimplemented syscall {}", syscall), state.pc.get());
  }
}
}  // namespace rv32
