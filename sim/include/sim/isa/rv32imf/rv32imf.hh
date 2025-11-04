// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Work with registry to add RV32IMF set.

#pragma once

#include "arith.hh"
#include "load_fp.hh"
#include "sim/instructions_registry.hh"
#include "store_fp.hh"

namespace rv32::rv32imf {

inline void registerInstructions(InstructionsRegistry& registry) {
  registry.add(std::make_unique<Fadd>());
}
}
