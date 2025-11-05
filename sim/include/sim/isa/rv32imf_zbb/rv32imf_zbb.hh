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
  registry.add(std::make_unique<Clz>());
  registry.add(std::make_unique<Ctz>());
  registry.add(std::make_unique<Cpop>());
  registry.add(std::make_unique<Max>());
  registry.add(std::make_unique<Maxu>());
  registry.add(std::make_unique<Min>());
  registry.add(std::make_unique<Minu>());
  registry.add(std::make_unique<Sextb>());
  registry.add(std::make_unique<Sexth>());
  registry.add(std::make_unique<Zexth>());
  registry.add(std::make_unique<Rol>());
  registry.add(std::make_unique<Ror>());
  registry.add(std::make_unique<Rori>());
  registry.add(std::make_unique<Orcb>());
  registry.add(std::make_unique<Rev8>());
}
}
