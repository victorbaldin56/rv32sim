// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Multiplication instructions.

#include "sim/instruction_templates.hh"
#include "sim/opcodes.hh"
#include "sim/operands.hh"

namespace rv32::rv32im {

struct OpMul {
  static constexpr std::string_view kName = "mul";
  static inline const ExtendedOpcode extended_opcode =
      Opcode37(RawOpcode::kOp, 0x0, 0x1);

  static Word eval(Word rs1, Word rs2) noexcept { return rs1 * rs2; }
};

using Mul = ArithInstruction<OpMul, RegValueGetter<OperandKind::kRS1>,
                             RegValueGetter<OperandKind::kRS2>>;

struct OpMulh {
  static constexpr std::string_view kName = "mulh";
  static inline const ExtendedOpcode extended_opcode =
      Opcode37(RawOpcode::kOp, 0x1, 0x1);

  static Word eval(Word rs1, Word rs2) noexcept {
    int64_t sx_rs1 = static_cast<int64_t>(std::bit_cast<SignedWord>(rs1));
    int64_t sx_rs2 = static_cast<int64_t>(std::bit_cast<SignedWord>(rs2));

    SignedWord res =
        static_cast<SignedWord>((sx_rs1 * sx_rs2) >> sizeof(Word) * 8);

    return std::bit_cast<Word>(res);
  }
};

using Mulh = ArithInstruction<OpMulh, RegValueGetter<OperandKind::kRS1>,
                              RegValueGetter<OperandKind::kRS2>>;

struct OpMulhsu {
  static constexpr std::string_view kName = "mulhsu";
  static inline const ExtendedOpcode extended_opcode =
      Opcode37(RawOpcode::kOp, 0x2, 0x1);

  static Word eval(Word rs1, Word rs2) noexcept {
    int64_t sx_rs1 = static_cast<int64_t>(std::bit_cast<SignedWord>(rs1));
    int64_t x_rs2 = static_cast<int64_t>(rs2);

    SignedWord res =
        static_cast<SignedWord>((sx_rs1 * x_rs2) >> sizeof(Word) * 8);

    return std::bit_cast<Word>(res);
  }
};

using Mulhsu = ArithInstruction<OpMulhsu, RegValueGetter<OperandKind::kRS1>,
                                RegValueGetter<OperandKind::kRS2>>;

struct OpMulhu {
  static constexpr std::string_view kName = "mulhu";
  static inline const ExtendedOpcode extended_opcode =
      Opcode37(RawOpcode::kOp, 0x3, 0x1);

  static Word eval(Word rs1, Word rs2) noexcept {
    uint64_t x_rs1 = static_cast<uint64_t>(rs1);
    uint64_t x_rs2 = static_cast<uint64_t>(rs2);

    return static_cast<Word>((x_rs1 * x_rs2) >> sizeof(Word) * 8);
  }
};

using Mulhu = ArithInstruction<OpMulhu, RegValueGetter<OperandKind::kRS1>,
                               RegValueGetter<OperandKind::kRS2>>;
}  // namespace rv32::rv32im
