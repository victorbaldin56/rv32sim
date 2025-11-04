// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Arithmetic instructions for floating point.

#pragma once

#include "sim/instruction_templates.hh"

namespace rv32::rv32imf {

struct OpFadd {
  static constexpr std::string_view kName = "fadd";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode5(RawOpcode::kOpFp, 0x0);

  static float eval(float rs1, float rs2) noexcept { return rs1 + rs2; }
};

using Fadd = ArithInstruction<OpFadd, RegValueGetter<OperandKind::kRS1, float>,
                              RegValueGetter<OperandKind::kRS2, float>>;
}
