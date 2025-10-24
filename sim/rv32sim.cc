// See LICENSE for license details.

// rv32sim - a simple RV32 simulator
//
// Simulator class implementation.

#include "sim/rv32sim.hh"

namespace RV32 {

Simulator::Simulator(const std::vector<std::string>& cmd) {
  auto elf_path = cmd.front();
  loadElf(elf_path);
}

void Simulator::loadElf(const std::filesystem::path& path) {}
}
