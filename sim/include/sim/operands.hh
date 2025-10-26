#pragma once

#include "base/bit_utils.hh"
#include "types.hh"

namespace rv32 {

struct Operands {
  RegNum rd;
  RegNum rs1;
  RegNum rs2;
  Immediate imm_i;
  Immediate imm_s;
  Immediate imm_u;
  Immediate imm_j;
};

constexpr Operands extractOperands(RawInstruction r) noexcept {
  return {.rd = bits::extractBits(r, 7, 11),
          .rs1 = bits::extractBits(r, 15, 19),
          .rs2 = bits::extractBits(r, 20, 24),
          .imm_i = bits::signExtend(bits::extractBits(r, 12, 20), 11),
          .imm_s = bits::signExtend(
              bits::extractBits(r, 7, 11) | (bits::extractBits(r, 25, 31) << 5),
              11),
          .imm_u = bits::signExtend(bits::extractBits(r, 12, 31) << 12, 31),
          .imm_j = bits::signExtend((bits::extractBits(r, 21, 30) << 1) |
                                        (bits::extractBits(r, 20, 20) << 11) |
                                        (bits::extractBits(r, 12, 19) << 12) |
                                        (bits::extractBits(r, 31, 31) << 20),
                                    20)};
};
}  // namespace rv32
