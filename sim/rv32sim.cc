// See LICENSE for license details.

// rv32sim - a simple RV32 simulator
//
// Simulator class implementation.

#include "sim/rv32sim.hh"

#include <numeric>

#include "base/bit_utils.hh"
#include "sim/config.hh"
#include "sim/elfloader.hh"

namespace RV32 {

Simulator::Simulator(const std::vector<std::string>& cmd) {
  auto elf_path = cmd.front();
  loadElf(elf_path);
  createExecutionEnvironment(cmd);
}

void Simulator::run() {}

void Simulator::createExecutionEnvironment(
    const std::vector<std::string>& cmd) {
  Word argc = cmd.size();
  Addr sp = Config::kStackTop -
            Config::kArgMax;  // to leave space to store whole argv strings
  Addr arg_string_addr = sp;
  sp -= (sizeof(Addr) * (argc + 1) +
         sizeof(Word));  // to store argc and argv pointers

  assert(Bits::isAligned(sp, Config::kStackAlignment));
  cpu_.set(Helpers::underlying(CPU::Registers::kSP),
           sp);  // at this point SP will be at program start

  mem_.emit(sp, argc);
  sp += sizeof(Word);

  for (const auto& arg : cmd) {
    mem_.copy(arg_string_addr, arg.c_str(), arg.size());
    mem_.emit(sp, arg_string_addr);
    sp += sizeof(Addr);
    arg_string_addr += arg.size();
  }

  mem_.emit(sp, static_cast<Addr>(0));  // argv[argc] = nullptr
  sp += sizeof(Addr);
}

void Simulator::loadElf(const std::filesystem::path& path) {
  ElfLoader loader(path);
  loader.load(mem_);
}
}
