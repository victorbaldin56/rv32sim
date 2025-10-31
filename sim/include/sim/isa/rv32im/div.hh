// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Division instructions.

#include "sim/instruction_templates.hh"
#include "sim/opcodes.hh"
#include "sim/operands.hh"

namespace rv32::rv32im {

struct OpDiv {
  static constexpr std::string_view kName = "div";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode37(RawOpcode::kOp, 0x4, 0x1);

  static Word eval(Word rs1, Word rs2) noexcept {
    SignedWord s_rs1 = std::bit_cast<SignedWord>(rs1);
    SignedWord s_rs2 = std::bit_cast<SignedWord>(rs2);

    return std::bit_cast<Word>(s_rs1 / s_rs2);
  }
};

using Div = ArithInstruction<OpDiv, RegValueGetter<OperandKind::kRS1>,
                              RegValueGetter<OperandKind::kRS2>>;

struct OpDivu {
  static constexpr std::string_view kName = "divu";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode37(RawOpcode::kOp, 0x5, 0x1);

  static Word eval(Word rs1, Word rs2) noexcept {
    return rs1 / rs2;
  }
};

using Divu = ArithInstruction<OpDivu, RegValueGetter<OperandKind::kRS1>,
                               RegValueGetter<OperandKind::kRS2>>;

struct OpRem {
  static constexpr std::string_view kName = "rem";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode37(RawOpcode::kOp, 0x6, 0x1);

  static Word eval(Word rs1, Word rs2) noexcept {
    SignedWord s_rs1 = std::bit_cast<SignedWord>(rs1);
    SignedWord s_rs2 = std::bit_cast<SignedWord>(rs2);

    return std::bit_cast<Word>(s_rs1 % s_rs2);
  }
};

using Rem = ArithInstruction<OpRem, RegValueGetter<OperandKind::kRS1>,
                              RegValueGetter<OperandKind::kRS2>>;

struct OpRemu {
  static constexpr std::string_view kName = "divu";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode37(RawOpcode::kOp, 0x7, 0x1);

  static Word eval(Word rs1, Word rs2) noexcept {
    return rs1 % rs2;
  }
};

using Remu = ArithInstruction<OpRemu, RegValueGetter<OperandKind::kRS1>,
                               RegValueGetter<OperandKind::kRS2>>;
}  // namespace rv32::rv32im
