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
  // arith
  registry.add(std::make_unique<Fadd>());
  registry.add(std::make_unique<Fsub>());
  registry.add(std::make_unique<Fmul>());
  registry.add(std::make_unique<Fdiv>());
  registry.add(std::make_unique<Fmax>());
  registry.add(std::make_unique<Fmin>());
  registry.add(std::make_unique<Fsqrt>());
  registry.add(std::make_unique<Fmadd>());
  registry.add(std::make_unique<Fmsub>());
  registry.add(std::make_unique<Fnmadd>());
  registry.add(std::make_unique<Fnmsub>());

  // load
  registry.add(std::make_unique<Flw>());

  // store
  registry.add(std::make_unique<Fsw>());
}
}
