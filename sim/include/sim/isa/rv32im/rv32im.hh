// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Work with registry to add RV32IM set.

#pragma once

#include "sim/instructions_registry.hh"
#include "mul.hh"
#include "div.hh"

namespace rv32::rv32im {

inline void registerInstructions(InstructionsRegistry& registry) {
  registry.add(std::make_unique<Mul>());
  registry.add(std::make_unique<Mulh>());
  registry.add(std::make_unique<Mulhsu>());
  registry.add(std::make_unique<Mulhu>());
  registry.add(std::make_unique<Div>());
  registry.add(std::make_unique<Divu>());
  registry.add(std::make_unique<Rem>());
  registry.add(std::make_unique<Remu>());
}
}  // namespace rv32::rv32im
