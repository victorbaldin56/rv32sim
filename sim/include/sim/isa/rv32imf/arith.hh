// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Arithmetic instructions for floating point.

#pragma once

#include <cmath>

#include "sim/instruction_templates.hh"

namespace rv32::rv32imf {

struct OpFadd {
  static constexpr std::string_view kName = "fadd.s";
  static inline const ExtendedOpcode extended_opcode =
      Opcode5(RawOpcode::kOpFp, 0x0);

  static float eval(float rs1, float rs2) noexcept { return rs1 + rs2; }
};

using Fadd = ArithInstruction<OpFadd, RegValueGetter<OperandKind::kRS1, float>,
                              RegValueGetter<OperandKind::kRS2, float>>;

struct OpFsub {
  static constexpr std::string_view kName = "fsub.s";
  static inline const ExtendedOpcode extended_opcode =
      Opcode5(RawOpcode::kOpFp, 0x1);

  static float eval(float rs1, float rs2) noexcept { return rs1 - rs2; }
};

using Fsub = ArithInstruction<OpFsub, RegValueGetter<OperandKind::kRS1, float>,
                              RegValueGetter<OperandKind::kRS2, float>>;

struct OpFmul {
  static constexpr std::string_view kName = "fmul.s";
  static inline const ExtendedOpcode extended_opcode =
      Opcode5(RawOpcode::kOpFp, 0x2);

  static float eval(float rs1, float rs2) noexcept { return rs1 * rs2; }
};

using Fmul = ArithInstruction<OpFmul, RegValueGetter<OperandKind::kRS1, float>,
                              RegValueGetter<OperandKind::kRS2, float>>;

struct OpFdiv {
  static constexpr std::string_view kName = "fdiv.s";
  static inline const ExtendedOpcode extended_opcode =
      Opcode5(RawOpcode::kOpFp, 0x3);

  static float eval(float rs1, float rs2) noexcept { return rs1 / rs2; }
};

using Fdiv = ArithInstruction<OpFdiv, RegValueGetter<OperandKind::kRS1, float>,
                              RegValueGetter<OperandKind::kRS2, float>>;

struct OpFmax {
  static constexpr std::string_view kName = "fmax.s";
  static inline const ExtendedOpcode extended_opcode =
      Opcode35(RawOpcode::kOpFp, 0x1, 0x5);

  static float eval(float rs1, float rs2) noexcept {
    return std::fmax(rs1, rs2);
  }
};

using Fmax = ArithInstruction<OpFmax, RegValueGetter<OperandKind::kRS1, float>,
                              RegValueGetter<OperandKind::kRS2, float>>;

struct OpFmin {
  static constexpr std::string_view kName = "fmin.s";
  static inline const ExtendedOpcode extended_opcode =
      Opcode35(RawOpcode::kOpFp, 0x0, 0x5);

  static float eval(float rs1, float rs2) noexcept {
    return std::fmin(rs1, rs2);
  }
};

using Fmin = ArithInstruction<OpFmin, RegValueGetter<OperandKind::kRS1, float>,
                              RegValueGetter<OperandKind::kRS2, float>>;

struct OpFsqrt {
  static constexpr std::string_view kName = "fsqrt.s";
  static inline const ExtendedOpcode extended_opcode =
      Opcode5(RawOpcode::kOpFp, 0xb);

  static float eval(float rs1) noexcept { return std::sqrt(rs1); }
};

using Fsqrt =
    ArithInstruction<OpFsqrt, RegValueGetter<OperandKind::kRS1, float>>;

struct OpFmadd {
  static constexpr std::string_view kName = "fmadd.s";
  static inline const ExtendedOpcode extended_opcode = Opcode(RawOpcode::kMAdd);

  static float eval(float rs1, float rs2, float rs3) noexcept {
    return std::fma(rs1, rs2, rs3);
  }
};

using Fmadd =
    ArithInstruction<OpFmadd, RegValueGetter<OperandKind::kRS1, float>,
                     RegValueGetter<OperandKind::kRS2, float>,
                     RegValueGetter<OperandKind::kRS3, float>>;

struct OpFmsub {
  static constexpr std::string_view kName = "fmsub.s";
  static inline const ExtendedOpcode extended_opcode = Opcode(RawOpcode::kMSub);

  static float eval(float rs1, float rs2, float rs3) noexcept {
    return std::fma(rs1, rs2, -rs3);
  }
};

using Fmsub =
    ArithInstruction<OpFmsub, RegValueGetter<OperandKind::kRS1, float>,
                     RegValueGetter<OperandKind::kRS2, float>,
                     RegValueGetter<OperandKind::kRS3, float>>;

struct OpFnmadd {
  static constexpr std::string_view kName = "fnmadd.s";
  static inline const ExtendedOpcode extended_opcode =
      Opcode(RawOpcode::kNMAdd);

  static float eval(float rs1, float rs2, float rs3) noexcept {
    return std::fma(-rs1, rs2, rs3);
  }
};

using Fnmadd =
    ArithInstruction<OpFnmadd, RegValueGetter<OperandKind::kRS1, float>,
                     RegValueGetter<OperandKind::kRS2, float>,
                     RegValueGetter<OperandKind::kRS3, float>>;

struct OpFnmsub {
  static constexpr std::string_view kName = "fnmsub.s";
  static inline const ExtendedOpcode extended_opcode =
      Opcode(RawOpcode::kNMSub);

  static float eval(float rs1, float rs2, float rs3) noexcept {
    return std::fma(-rs1, rs2, -rs3);
  }
};

using Fnmsub =
    ArithInstruction<OpFnmsub, RegValueGetter<OperandKind::kRS1, float>,
                     RegValueGetter<OperandKind::kRS2, float>,
                     RegValueGetter<OperandKind::kRS3, float>>;

struct OpFeq {
  static constexpr std::string_view kName = "feq";
  static inline const ExtendedOpcode extended_opcode =
      Opcode35(RawOpcode::kOpFp, 0x2, 0x14);

  static Word eval(float rs1, float rs2) noexcept { return rs1 == rs2; }
};

using Feq = ArithInstruction<OpFeq, RegValueGetter<OperandKind::kRS1, float>,
                             RegValueGetter<OperandKind::kRS2, float>>;

struct OpFlt {
  static constexpr std::string_view kName = "flt";
  static inline const ExtendedOpcode extended_opcode =
      Opcode35(RawOpcode::kOpFp, 0x1, 0x14);

  static Word eval(float rs1, float rs2) noexcept { return rs1 < rs2; }
};

using Flt = ArithInstruction<OpFlt, RegValueGetter<OperandKind::kRS1, float>,
                             RegValueGetter<OperandKind::kRS2, float>>;

struct OpFle {
  static constexpr std::string_view kName = "fle";
  static inline const ExtendedOpcode extended_opcode =
      Opcode35(RawOpcode::kOpFp, 0x0, 0x14);

  static Word eval(float rs1, float rs2) noexcept { return rs1 <= rs2; }
};

using Fle = ArithInstruction<OpFle, RegValueGetter<OperandKind::kRS1, float>,
                             RegValueGetter<OperandKind::kRS2, float>>;

struct OpFmvxw {
  static constexpr std::string_view kName = "fmv.x.w";
  static inline const ExtendedOpcode extended_opcode =
      Opcode35(RawOpcode::kOpFp, 0x0, 0x1c);

  static Word eval(float rs1) noexcept { return std::bit_cast<Word>(rs1); }
};

using Fmvxw =
    ArithInstruction<OpFmvxw, RegValueGetter<OperandKind::kRS1, float>>;

struct OpFmvwx {
  static constexpr std::string_view kName = "fmv.w.x";
  static inline const ExtendedOpcode extended_opcode =
      Opcode35(RawOpcode::kOpFp, 0x0, 0x1e);

  static float eval(Word rs1) noexcept { return std::bit_cast<float>(rs1); }
};

using Fmvwx = ArithInstruction<OpFmvwx, RegValueGetter<OperandKind::kRS1>>;

struct OpFcvtw {
  static constexpr std::string_view kName = "fcvt.w.s";
  static inline const ExtendedOpcode extended_opcode =
      Opcode5RS2(RawOpcode::kOpFp, 0x18, 0x0);

  static SignedWord eval(float rs1) noexcept { return std::lrint(rs1); }
};

using Fcvtw =
    ArithInstruction<OpFcvtw, RegValueGetter<OperandKind::kRS1, float>>;

struct OpFcvtwu {
  static constexpr std::string_view kName = "fcvt.wu.s";  // FIXME
  static inline const ExtendedOpcode extended_opcode =
      Opcode5RS2(RawOpcode::kOpFp, 0x18, 0x1);

  static Word eval(float rs1) noexcept { return std::lrint(rs1); }
};

using Fcvtwu =
    ArithInstruction<OpFcvtwu, RegValueGetter<OperandKind::kRS1, float>>;

struct OpFcvtsw {
  static constexpr std::string_view kName = "fcvt.s.w";
  static inline const ExtendedOpcode extended_opcode =
      Opcode5RS2(RawOpcode::kOpFp, 0x1a, 0x0);

  static float eval(SignedWord rs1) noexcept { return static_cast<float>(rs1); }
};

using Fcvtsw = ArithInstruction<OpFcvtsw, RegValueGetter<OperandKind::kRS1>>;

struct OpFcvtswu {
  static constexpr std::string_view kName = "fcvt.s.wu";
  static inline const ExtendedOpcode extended_opcode =
      Opcode5RS2(RawOpcode::kOpFp, 0x1a, 0x1);

  static float eval(Word rs1) noexcept { return static_cast<float>(rs1); }
};

using Fcvtswu = ArithInstruction<OpFcvtswu, RegValueGetter<OperandKind::kRS1>>;

struct OpFsgnj {
  static constexpr std::string_view kName = "fsgnj.s";
  static inline const ExtendedOpcode extended_opcode =
      Opcode35(RawOpcode::kOpFp, 0x0, 0x4);

  static float eval(float rs1, float rs2) noexcept {
    Word a = std::bit_cast<Word>(rs1);
    Word b = std::bit_cast<Word>(rs2);
    Word sign = b & 0x80000000u;          // sign from rs2
    Word out = (a & 0x7fffffffu) | sign;  // keep magnitude of rs1
    return std::bit_cast<float>(out);
  }
};

using Fsgnj =
    ArithInstruction<OpFsgnj, RegValueGetter<OperandKind::kRS1, float>,
                     RegValueGetter<OperandKind::kRS2, float>>;

struct OpFsgnjn {
  static constexpr std::string_view kName = "fsgnjn.s";
  static inline const ExtendedOpcode extended_opcode =
      Opcode35(RawOpcode::kOpFp, 0x1, 0x4);

  static float eval(float rs1, float rs2) noexcept {
    Word a = std::bit_cast<Word>(rs1);
    Word b = std::bit_cast<Word>(rs2);
    Word sign = (~b) & 0x80000000u;       // opposite sign from rs2
    Word out = (a & 0x7fffffffu) | sign;  // keep magnitude of rs1
    return std::bit_cast<float>(out);
  }
};

using Fsgnjn =
    ArithInstruction<OpFsgnjn, RegValueGetter<OperandKind::kRS1, float>,
                     RegValueGetter<OperandKind::kRS2, float>>;

struct OpFsgnjx {
  static constexpr std::string_view kName = "fsgnjx.s";
  static inline const ExtendedOpcode extended_opcode =
      Opcode35(RawOpcode::kOpFp, 0x2, 0x4);

  static float eval(float rs1, float rs2) noexcept {
    Word a = std::bit_cast<Word>(rs1);
    Word b = std::bit_cast<Word>(rs2);
    Word sign = (a ^ b) & 0x80000000u;    // xor of sign bits
    Word out = (a & 0x7fffffffu) | sign;  // keep magnitude of rs1
    return std::bit_cast<float>(out);
  }
};

using Fsgnjx =
    ArithInstruction<OpFsgnjx, RegValueGetter<OperandKind::kRS1, float>,
                     RegValueGetter<OperandKind::kRS2, float>>;

struct OpFclass {
  static constexpr std::string_view kName = "fclass.s";
  static inline const ExtendedOpcode extended_opcode =
      Opcode35RS2(RawOpcode::kOpFp, 0x1, 0x1c, 0x0);

  static std::uint32_t eval(float rs1) noexcept {
    Word u = std::bit_cast<Word>(rs1);
    const Word sign = (u >> 31) & 1u;
    const Word exp = (u >> 23) & 0xffu;
    const Word frac = u & 0x7fffffu;

    Word mask = 0u;
    if (exp == 0xffu) {
      if (frac == 0u) {
        // infinity
        mask = (sign ? (1u << 0) : (1u << 7));
      } else {
        // NaN: spec: top bit of fraction (bit 22) = quiet indicator
        const bool quiet = (frac & (1u << 22)) != 0;
        mask = quiet ? (1u << 9) : (1u << 8);
      }
    } else if (exp == 0u) {
      if (frac == 0u) {
        // zero
        mask = (sign ? (1u << 3) : (1u << 4));
      } else {
        // subnormal
        mask = (sign ? (1u << 2) : (1u << 5));
      }
    } else {
      // normal numbers
      mask = (sign ? (1u << 1) : (1u << 6));
    }
    return mask;
  }
};

using Fclass =
    ArithInstruction<OpFclass, RegValueGetter<OperandKind::kRS1, float>>;
}
