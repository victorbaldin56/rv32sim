// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Arithmetic instructions for floating point.

#pragma once

#include <cmath>

#include "sim/instruction_templates.hh"

namespace rv32::rv32imf {

struct OpFadd {
  static constexpr std::string_view kName = "fadd";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode35(RawOpcode::kOpFp, 0x0, 0x0);

  static float eval(float rs1, float rs2) noexcept { return rs1 + rs2; }
};

using Fadd = ArithInstruction<OpFadd, RegValueGetter<OperandKind::kRS1, float>,
                              RegValueGetter<OperandKind::kRS2, float>>;

struct OpFsub {
  static constexpr std::string_view kName = "fsub";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode35(RawOpcode::kOpFp, 0x0, 0x1);

  static float eval(float rs1, float rs2) noexcept { return rs1 - rs2; }
};

using Fsub = ArithInstruction<OpFsub, RegValueGetter<OperandKind::kRS1, float>,
                              RegValueGetter<OperandKind::kRS2, float>>;

struct OpFmul {
  static constexpr std::string_view kName = "fmul";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode35(RawOpcode::kOpFp, 0x0, 0x2);

  static float eval(float rs1, float rs2) noexcept { return rs1 * rs2; }
};

using Fmul = ArithInstruction<OpFmul, RegValueGetter<OperandKind::kRS1, float>,
                              RegValueGetter<OperandKind::kRS2, float>>;

struct OpFdiv {
  static constexpr std::string_view kName = "fdiv";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode35(RawOpcode::kOpFp, 0x0, 0x3);

  static float eval(float rs1, float rs2) noexcept { return rs1 / rs2; }
};

using Fdiv = ArithInstruction<OpFdiv, RegValueGetter<OperandKind::kRS1, float>,
                              RegValueGetter<OperandKind::kRS2, float>>;

struct OpFmax {
  static constexpr std::string_view kName = "fmax";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode35(RawOpcode::kOpFp, 0x1, 0x5);

  static float eval(float rs1, float rs2) noexcept {
    return std::fmax(rs1, rs2);
  }
};

using Fmax = ArithInstruction<OpFmax, RegValueGetter<OperandKind::kRS1, float>,
                              RegValueGetter<OperandKind::kRS2, float>>;

struct OpFmin {
  static constexpr std::string_view kName = "fmin";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode35(RawOpcode::kOpFp, 0x0, 0x5);

  static float eval(float rs1, float rs2) noexcept {
    return std::fmin(rs1, rs2);
  }
};

using Fmin = ArithInstruction<OpFmin, RegValueGetter<OperandKind::kRS1, float>,
                              RegValueGetter<OperandKind::kRS2, float>>;

struct OpFsqrt {
  static constexpr std::string_view kName = "fsqrt";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode35(RawOpcode::kOpFp, 0x0, 0xb);

  static float eval(float rs1) noexcept { return std::sqrt(rs1); }
};

using Fsqrt =
    ArithInstruction<OpFsqrt, RegValueGetter<OperandKind::kRS1, float>>;

struct OpFmadd {
  static constexpr std::string_view kName = "fmadd";
  static constexpr ExtendedOpcode kExtendedOpcode = Opcode(RawOpcode::kMAdd);

  static float eval(float rs1, float rs2, float rs3) noexcept {
    return std::fma(rs1, rs2, rs3);
  }
};

using Fmadd =
    ArithInstruction<OpFmadd, RegValueGetter<OperandKind::kRS1, float>,
                     RegValueGetter<OperandKind::kRS2, float>,
                     RegValueGetter<OperandKind::kRS3, float>>;

struct OpFmsub {
  static constexpr std::string_view kName = "fmsub";
  static constexpr ExtendedOpcode kExtendedOpcode = Opcode(RawOpcode::kMSub);

  static float eval(float rs1, float rs2, float rs3) noexcept {
    return std::fma(rs1, rs2, -rs3);
  }
};

using Fmsub =
    ArithInstruction<OpFmsub, RegValueGetter<OperandKind::kRS1, float>,
                     RegValueGetter<OperandKind::kRS2, float>,
                     RegValueGetter<OperandKind::kRS3, float>>;

struct OpFnmadd {
  static constexpr std::string_view kName = "fnmadd";
  static constexpr ExtendedOpcode kExtendedOpcode = Opcode(RawOpcode::kNMAdd);

  static float eval(float rs1, float rs2, float rs3) noexcept {
    return std::fma(-rs1, rs2, rs3);
  }
};

using Fnmadd =
    ArithInstruction<OpFnmadd, RegValueGetter<OperandKind::kRS1, float>,
                     RegValueGetter<OperandKind::kRS2, float>,
                     RegValueGetter<OperandKind::kRS3, float>>;

struct OpFnmsub {
  static constexpr std::string_view kName = "fnmsub";
  static constexpr ExtendedOpcode kExtendedOpcode = Opcode(RawOpcode::kNMSub);

  static float eval(float rs1, float rs2, float rs3) noexcept {
    return std::fma(-rs1, rs2, -rs3);
  }
};

using Fnmsub =
    ArithInstruction<OpFnmsub, RegValueGetter<OperandKind::kRS1, float>,
                     RegValueGetter<OperandKind::kRS2, float>,
                     RegValueGetter<OperandKind::kRS3, float>>;
}
