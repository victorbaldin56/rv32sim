// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Work with registry to add RV32IMF_ZBB set.

#pragma once

#include "arith.hh"
#include "sim/instructions_registry.hh"

namespace rv32::rv32imf_zbb {

inline void registerInstructions(InstructionsRegistry& registry) {
  registry.add(std::make_unique<Andn>());
  registry.add(std::make_unique<Orn>());
  registry.add(std::make_unique<Xnor>());
}
}
