#include "sim/decoder.hh"

#include "base/bit_utils.hh"
#include "sim/opcodes.hh"
/*
namespace rv32 {
namespace {

InstructionDecodeInfoTypeR decodeTypeR(RawInstruction raw) {
  return {.opcode = bits::extractBits(raw, 0, 6),
          .rd = bits::extractBits(raw, 7, 11),
          .funct3 = bits::extractBits(raw, 12, 14),
          .rs1 = bits::extractBits(raw, 15, 19),
          .rs2 = bits::extractBits(raw, 20, 24),
          .funct7 = bits::extractBits(raw, 25, 31)};
}

InstructionDecodeInfoTypeI decodeTypeI(RawInstruction raw) {
  std::uint32_t imm12 = bits::extractBits(raw, 20, 31);
  return {.opcode = bits::extractBits(raw, 0, 6),
          .rd = bits::extractBits(raw, 7, 11),
          .funct3 = bits::extractBits(raw, 12, 14),
          .rs1 = bits::extractBits(raw, 15, 19),
          .imm = bits::signExtend(imm12, 12)};
}

InstructionDecodeInfoTypeS decodeTypeS(RawInstruction raw) {
  std::uint32_t imm5_11 = bits::extractBits(raw, 25, 31);
  std::uint32_t imm0_4 = bits::extractBits(raw, 7, 11);
  std::uint32_t imm12 = (imm5_11 << 5) | imm0_4;
  return {.opcode = bits::extractBits(raw, 0, 6),
          .funct3 = bits::extractBits(raw, 12, 14),
          .rs1 = bits::extractBits(raw, 15, 19),
          .rs2 = bits::extractBits(raw, 20, 24),
          .imm = bits::signExtend(imm12, 12)};
}

InstructionDecodeInfoTypeB decodeTypeB(RawInstruction raw) {
  std::uint32_t imm12 = bits::extractBits(raw, 31, 31);
  std::uint32_t imm10_5 = bits::extractBits(raw, 25, 30);
  std::uint32_t imm4_1 = bits::extractBits(raw, 8, 11);
  std::uint32_t imm11 = bits::extractBits(raw, 7, 7);
  std::uint32_t imm13 =
      (imm12 << 12) | (imm11 << 11) | (imm10_5 << 5) | (imm4_1 << 1);
  return {.opcode = bits::extractBits(raw, 0, 6),
          .funct3 = bits::extractBits(raw, 12, 14),
          .rs1 = bits::extractBits(raw, 15, 19),
          .rs2 = bits::extractBits(raw, 20, 24),
          .imm = bits::signExtend(imm13, 13)};
}

InstructionDecodeInfoTypeU decodeTypeU(RawInstruction raw) {
  std::uint32_t upper_u = bits::extractBits(raw, 12, 31);
  std::int32_t upper_i = static_cast<std::int32_t>(upper_u << 12);
  return {.opcode = bits::extractBits(raw, 0, 6),
          .rd = bits::extractBits(raw, 7, 11),
          .imm = upper_i};
}

InstructionDecodeInfoTypeJ decodeTypeJ(RawInstruction raw) {
  std::uint32_t imm20 = bits::extractBits(raw, 31, 31);
  std::uint32_t imm10_1 = bits::extractBits(raw, 21, 30);
  std::uint32_t imm11 = bits::extractBits(raw, 20, 20);
  std::uint32_t imm19_12 = bits::extractBits(raw, 12, 19);
  std::uint32_t imm21 =
      (imm20 << 20) | (imm19_12 << 12) | (imm11 << 11) | (imm10_1 << 1);
  return {.opcode = bits::extractBits(raw, 0, 6),
          .rd = bits::extractBits(raw, 7, 11),
          .imm = bits::signExtend(imm21, 21)};
}
}  // namespace

InstructionDecodeInfo decodeInstruction(RawInstruction raw) {
  return std::make_tuple(decodeTypeR(raw), decodeTypeI(raw), decodeTypeS(raw),
                         decodeTypeB(raw), decodeTypeU(raw), decodeTypeJ(raw));
}
}  // namespace rv32
*/