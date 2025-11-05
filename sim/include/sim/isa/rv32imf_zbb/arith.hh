// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Arithmetic instructions for bit manipulation.

#pragma once

#include <bit>

#include "sim/instruction_templates.hh"

namespace rv32::rv32imf_zbb {

struct OpAndn {
  static constexpr std::string_view kName = "andn";
  static inline const ExtendedOpcode extended_opcode =
      Opcode37(RawOpcode::kOp, 0x7, 0x20);

  static Word eval(Word rs1, Word rs2) noexcept { return rs1 & ~rs2; }
};

using Andn = ArithInstruction<OpAndn, RegValueGetter<OperandKind::kRS1>,
                              RegValueGetter<OperandKind::kRS2>>;

struct OpOrn {
  static constexpr std::string_view kName = "orn";
  static inline const ExtendedOpcode extended_opcode =
      Opcode37(RawOpcode::kOp, 0x6, 0x20);

  static Word eval(Word rs1, Word rs2) noexcept { return rs1 | ~rs2; }
};

using Orn = ArithInstruction<OpOrn, RegValueGetter<OperandKind::kRS1>,
                             RegValueGetter<OperandKind::kRS2>>;

struct OpXnor {
  static constexpr std::string_view kName = "xnor";
  static inline const ExtendedOpcode extended_opcode =
      Opcode37(RawOpcode::kOp, 0x4, 0x20);

  static Word eval(Word rs1, Word rs2) noexcept { return ~(rs1 ^ rs2); }
};

using Xnor = ArithInstruction<OpXnor, RegValueGetter<OperandKind::kRS1>,
                              RegValueGetter<OperandKind::kRS2>>;

struct OpClz {
  static constexpr std::string_view kName = "clz";
  static inline const ExtendedOpcode extended_opcode =
      Opcode37RS2(RawOpcode::kOpImm, 0x1, 0x30, 0x0);

  static Word eval(Word rs1) noexcept { return std::countl_zero(rs1); }
};

using Clz = ArithInstruction<OpClz, RegValueGetter<OperandKind::kRS1>>;

struct OpCtz {
  static constexpr std::string_view kName = "ctz";
  static inline const ExtendedOpcode extended_opcode =
      Opcode37RS2(RawOpcode::kOpImm, 0x1, 0x30, 0x1);

  static Word eval(Word rs1) noexcept { return std::countr_zero(rs1); }
};

using Ctz = ArithInstruction<OpCtz, RegValueGetter<OperandKind::kRS1>>;

struct OpCpop {
  static constexpr std::string_view kName = "cpop";
  static inline const ExtendedOpcode extended_opcode =
      Opcode37RS2(RawOpcode::kOpImm, 0x1, 0x30, 0x2);

  static Word eval(Word rs1) noexcept { return std::popcount(rs1); }
};

using Cpop = ArithInstruction<OpCpop, RegValueGetter<OperandKind::kRS1>>;

struct OpMax {
  static constexpr std::string_view kName = "max";
  static inline const ExtendedOpcode extended_opcode =
      Opcode37(RawOpcode::kOp, 0x6, 0x5);

  static SignedWord eval(SignedWord rs1, SignedWord rs2) noexcept {
    return std::max(rs1, rs2);
  }
};

using Max = ArithInstruction<OpMax, RegValueGetter<OperandKind::kRS1>,
                             RegValueGetter<OperandKind::kRS2>>;

struct OpMaxu {
  static constexpr std::string_view kName = "maxu";
  static inline const ExtendedOpcode extended_opcode =
      Opcode37(RawOpcode::kOp, 0x7, 0x5);

  static Word eval(Word rs1, Word rs2) noexcept { return std::max(rs1, rs2); }
};

using Maxu = ArithInstruction<OpMaxu, RegValueGetter<OperandKind::kRS1>,
                              RegValueGetter<OperandKind::kRS2>>;

struct OpMin {
  static constexpr std::string_view kName = "min";
  static inline const ExtendedOpcode extended_opcode =
      Opcode37(RawOpcode::kOp, 0x4, 0x5);

  static SignedWord eval(SignedWord rs1, SignedWord rs2) noexcept {
    return std::min(rs1, rs2);
  }
};

using Min = ArithInstruction<OpMin, RegValueGetter<OperandKind::kRS1>,
                             RegValueGetter<OperandKind::kRS2>>;

struct OpMinu {
  static constexpr std::string_view kName = "minu";
  static inline const ExtendedOpcode extended_opcode =
      Opcode37(RawOpcode::kOp, 0x5, 0x5);

  static Word eval(Word rs1, Word rs2) noexcept { return std::min(rs1, rs2); }
};

using Minu = ArithInstruction<OpMinu, RegValueGetter<OperandKind::kRS1>,
                              RegValueGetter<OperandKind::kRS2>>;

struct OpSextb {
  static constexpr std::string_view kName = "sext.b";
  static inline const ExtendedOpcode extended_opcode =
      Opcode37RS2(RawOpcode::kOpImm, 0x1, 0x30, 0x4);

  static Word eval(Word rs1) noexcept {
    return bits::signExtend(rs1 & bits::bitMask<Byte>(), 8);
  }
};

using Sextb = ArithInstruction<OpSextb, RegValueGetter<OperandKind::kRS1>>;

struct OpSexth {
  static constexpr std::string_view kName = "sext.h";
  static inline const ExtendedOpcode extended_opcode =
      Opcode37RS2(RawOpcode::kOpImm, 0x1, 0x30, 0x5);

  static Word eval(Word rs1) noexcept {
    return bits::signExtend(rs1 & bits::bitMask<Half>(), 16);
  }
};

using Sexth = ArithInstruction<OpSexth, RegValueGetter<OperandKind::kRS1>>;

struct OpZexth {
  static constexpr std::string_view kName = "zext.h";
  static inline const ExtendedOpcode extended_opcode =
      Opcode37RS2(RawOpcode::kOp, 0x4, 0x4, 0x0);

  static Word eval(Word rs1) noexcept { return rs1 & bits::bitMask<Half>(16); }
};

using Zexth = ArithInstruction<OpZexth, RegValueGetter<OperandKind::kRS1>>;

struct OpRol {
  static constexpr std::string_view kName = "rol";
  static inline const ExtendedOpcode extended_opcode =
      Opcode37(RawOpcode::kOp, 0x1, 0x30);

  static Word eval(Word rs1, Word rs2) noexcept { return std::rotl(rs1, rs2); }
};

using Rol = ArithInstruction<OpRol, RegValueGetter<OperandKind::kRS1>,
                             RegValueGetter<OperandKind::kRS2>>;

struct OpRor {
  static constexpr std::string_view kName = "ror";
  static inline const ExtendedOpcode extended_opcode =
      Opcode37(RawOpcode::kOp, 0x5, 0x30);

  static Word eval(Word rs1, Word rs2) noexcept { return std::rotr(rs1, rs2); }
};

using Ror = ArithInstruction<OpRor, RegValueGetter<OperandKind::kRS1>,
                             RegValueGetter<OperandKind::kRS2>>;

struct OpRori {
  static constexpr std::string_view kName = "rori";
  static inline const ExtendedOpcode extended_opcode =
      Opcode37(RawOpcode::kOpImm, 0x5, 0x30);

  static Word eval(Word rs1, Word shamt) noexcept {
    return std::rotr(rs1, shamt);
  }
};

using Rori = ArithInstruction<OpRori, RegValueGetter<OperandKind::kRS1>,
                              ImmGetter<OperandKind::kShamt>>;

struct OpOrcb {
  static constexpr std::string_view kName = "orc.b";
  static inline const ExtendedOpcode extended_opcode =
      Opcode312(RawOpcode::kOpImm, 0x5, 0x287);

  static Word eval(Word rs) noexcept {
    auto get_byte = [](Word x, unsigned num) {
      return bits::extractBits(x, num * sizeof(Word),
                               (num + 1) * sizeof(Word) - 1)
                 ? 0xff
                 : 0x0;
    };

    return (get_byte(rs, 0) << 0) | (get_byte(rs, 1) << 8) |
           (get_byte(rs, 2) << 16) | (get_byte(rs, 3) << 24);
  }
};

using Orcb = ArithInstruction<OpOrcb, RegValueGetter<OperandKind::kRS1>>;

struct OpRev8 {
  static constexpr std::string_view kName = "rev8";
  static inline const ExtendedOpcode extended_opcode =
      Opcode312(RawOpcode::kOpImm, 0x5, 0x698);

  static Word eval(Word rs) noexcept {
    return (bits::extractBits(rs, 0, 7) << 24) |
           (bits::extractBits(rs, 8, 15) << 16) |
           (bits::extractBits(rs, 16, 23) << 8) |
           (bits::extractBits(rs, 24, 31) << 0);
  }
};

using Rev8 = ArithInstruction<OpRev8, RegValueGetter<OperandKind::kRS1>>;
}  // namespace rv32::rv32imf_zbb
