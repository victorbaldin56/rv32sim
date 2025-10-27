#pragma once

#include "arith.hh"
#include "branch.hh"
#include "jal.hh"
#include "load.hh"
#include "misc_mem.hh"
#include "sim/instructions_registry.hh"
#include "store.hh"
#include "system.hh"

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

  // jal
  registry.add(std::make_unique<Jal>());

  /// jalr
  registry.add(std::make_unique<Jalr>());

  // branch
  registry.add(std::make_unique<Beq>());
  registry.add(std::make_unique<Bne>());
  registry.add(std::make_unique<Blt>());
  registry.add(std::make_unique<Bge>());
  registry.add(std::make_unique<Bltu>());
  registry.add(std::make_unique<Bgeu>());

  // load
  registry.add(std::make_unique<Lb>());
  registry.add(std::make_unique<Lh>());
  registry.add(std::make_unique<Lw>());
  registry.add(std::make_unique<Lbu>());
  registry.add(std::make_unique<Lhu>());

  /// store
  registry.add(std::make_unique<Sb>());
  registry.add(std::make_unique<Sh>());
  registry.add(std::make_unique<Sw>());

  /// misc mem
  registry.add(std::make_unique<Fence>());

  /// system
  registry.add(std::make_unique<Ecall>());
  registry.add(std::make_unique<Ebreak>());
}
}  // namespace rv32::rv32i
