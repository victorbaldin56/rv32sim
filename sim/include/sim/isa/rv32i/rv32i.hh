#pragma once

#include "arith.hh"
#include "sim/instructions_registry.hh"

namespace rv32::rv32i {

inline void registerInstructions(InstructionsRegistry& registry) {
  // arith
  registry.add(std::make_unique<Lui>());
  registry.add(std::make_unique<Auipc>());
  registry.add(std::make_unique<Addi>());
  registry.add(std::make_unique<Slti>());
  registry.add(std::make_unique<Sltiu>());
  registry.add(std::make_unique<Xori>());
  registry.add(std::make_unique<Ori>());
  registry.add(std::make_unique<Andi>());
  registry.add(std::make_unique<Slli>());
  registry.add(std::make_unique<Srli>());
  registry.add(std::make_unique<Srai>());
  registry.add(std::make_unique<Add>());
  registry.add(std::make_unique<Sub>());
  registry.add(std::make_unique<Sll>());
  registry.add(std::make_unique<Slt>());
  registry.add(std::make_unique<Sltu>());
  registry.add(std::make_unique<Xor>());
  registry.add(std::make_unique<Srl>());
  registry.add(std::make_unique<Sra>());
  registry.add(std::make_unique<Or>());
  registry.add(std::make_unique<And>());
}
}  // namespace rv32::rv32i
