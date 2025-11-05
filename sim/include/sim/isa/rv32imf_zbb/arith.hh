// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Arithmetic instructions for bit manipulation.

#pragma once

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
}  // namespace rv32::rv32imf_zbb
