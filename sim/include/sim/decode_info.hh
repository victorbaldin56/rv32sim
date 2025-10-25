#pragma once

#include "types.hh"

namespace RV32 {

struct InstructionDecodeInfoTypeR {
  Word opcode;
  Word rd;
  Word funct3;
  Word rs1;
  Word rs2;
  Word funct7;
};

struct InstructionDecodeInfoTypeI {
  Word opcode;
  Word rd;
  Word funct3;
  Word rs1;
  Word imm;
};

struct InstructionDecodeInfoTypeS {
  Word opcode;
  Word funct3;
  Word rs1;
  Word rs2;
  Word imm;
};

struct InstructionDecodeInfoTypeU {
  Word opcode;
  Word rd;
  Word imm;
};

struct InstructionDecodeInfoTypeB {
  Word opcode;
  Word funct3;
  Word rs1;
  Word rs2;
  Word imm;
};

struct InstructionDecodeInfoTypeJ {
  Word opcode;
  Word rd;
  Word imm;
};

InstructionDecodeInfoTypeR decodeInstructionTypeR(RawInstruction instr);
InstructionDecodeInfoTypeI decodeInstructionTypeI(RawInstruction instr);
InstructionDecodeInfoTypeS decodeInstructionTypeS(RawInstruction instr);
InstructionDecodeInfoTypeU decodeInstructionTypeU(RawInstruction instr);
InstructionDecodeInfoTypeB decodeInstructionTypeB(RawInstruction instr);
InstructionDecodeInfoTypeJ decodeInstructionTypeJ(RawInstruction instr);
}
