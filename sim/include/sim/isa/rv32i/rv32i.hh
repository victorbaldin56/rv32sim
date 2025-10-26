#pragma once

#include "arith.hh"
#include "sim/instructions_registry.hh"

namespace rv32::rv32i {

inline void registerInstructions(InstructionsRegistry& registry) {
  registry.add(std::make_unique<Lui>());
}
}  // namespace rv32::rv32i
