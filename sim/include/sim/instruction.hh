// See LICENSE for license details.

// rv32sim - a simple RV32 simulator
//
// TODO

#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include "rv32sim.hh"

namespace RV32 {

class IInstruction {
 public:
  static std::unique_ptr<IInstruction> create(RawInstruction raw_instruction);

  enum class ExecutionResult { kOk, kExit };

  virtual ExecutionResult execute(Simulator& sim) = 0;  // FIXME
  virtual std::string getName() const = 0;
  virtual ~IInstruction() {}
};

class InstructionTypeR : public IInstruction {
 protected:
  Word opcode_;
  Word rd_;
  Word funct3_;
  Word rs1_;
  Word rs2_;
  Word funct7_;
};

class InstructionTypeI : public IInstruction {
 protected:
  Word opcode_;
  Word rd_;
  Word funct3_;
  Word rs1_;
  Word imm_;
};

class InstructionTypeS : public IInstruction {
 protected:
  Word opcode_;
  Word funct3_;
  Word rs1_;
  Word rs2_;
  Word imm_;
};

class InstructionTypeU : public IInstruction {
 protected:
  Word opcode_;
  Word rd_;
  Word imm_;
};

class InstructionTypeB : public IInstruction {
 protected:
  Word opcode_;
  Word funct3_;
  Word rs1_;
  Word rs2_;
  Word imm_;
};

class InstructionTypeJ : public IInstruction {
 protected:
  Word opcode_;
  Word rd_;
  Word imm_;
};
}
