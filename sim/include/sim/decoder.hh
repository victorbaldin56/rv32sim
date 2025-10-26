#pragma once

#include <tuple>

#include "types.hh"

namespace rv32 {

struct InstructionDecodeInfoTypeR {
  std::uint32_t opcode;
  std::uint32_t rd;
  std::uint32_t funct3;
  std::uint32_t rs1;
  std::uint32_t rs2;
  std::uint32_t funct7;
};

struct InstructionDecodeInfoTypeI {
  std::uint32_t opcode;
  std::uint32_t rd;
  std::uint32_t funct3;
  std::uint32_t rs1;
  std::int32_t imm;
};

struct InstructionDecodeInfoTypeS {
  std::uint32_t opcode;
  std::uint32_t funct3;
  std::uint32_t rs1;
  std::uint32_t rs2;
  std::int32_t imm;
};

struct InstructionDecodeInfoTypeB {
  std::uint32_t opcode;
  std::uint32_t funct3;
  std::uint32_t rs1;
  std::uint32_t rs2;
  std::int32_t imm;
};

struct InstructionDecodeInfoTypeU {
  std::uint32_t opcode;
  std::uint32_t rd;
  std::int32_t imm;
};

struct InstructionDecodeInfoTypeJ {
  std::uint32_t opcode;
  std::uint32_t rd;
  std::int32_t imm;
};

// we will decide which encoding is correct after lookup in registry.
// this is for better code without duplication
using InstructionDecodeInfo =
    std::tuple<InstructionDecodeInfoTypeR, InstructionDecodeInfoTypeI,
               InstructionDecodeInfoTypeS, InstructionDecodeInfoTypeB,
               InstructionDecodeInfoTypeU, InstructionDecodeInfoTypeJ>;

InstructionDecodeInfo decodeInstruction(RawInstruction raw);
}
