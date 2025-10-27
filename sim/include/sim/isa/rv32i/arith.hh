#pragma once

#include "sim/basic_instruction.hh"
#include "sim/opcodes.hh"
#include "sim/operands.hh"

namespace rv32::rv32i {
struct OpLui {
  static constexpr std::string_view kName = "lui";
  static constexpr ExtendedOpcode kExtendedOpcode = Opcode(RawOpcode::kLui);

  static Word eval(Word imm) noexcept { return imm; }
};

using Lui = ArithInstruction<OpLui, ImmGetter<OperandKind::kImmU>>;

struct OpAuipc {
  static constexpr std::string_view kName = "auipc";
  static constexpr ExtendedOpcode kExtendedOpcode = Opcode(RawOpcode::kAuipc);

  static Word eval(Addr pc, Word imm) noexcept { return pc + imm; }
};

using Auipc =
    ArithInstruction<OpAuipc, PCValueGetter, ImmGetter<OperandKind::kImmU>>;

struct OpAddi {
  static constexpr std::string_view kName = "addi";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kOpImm, 0x0);

  static Word eval(Word rs1, Word imm) noexcept { return rs1 + imm; }
};

using Addi = ArithInstruction<OpAddi, RegValueGetter<OperandKind::kRS1>,
                              ImmGetter<OperandKind::kImmI>>;

struct OpSlti {
  static constexpr const char* kName = "slti";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kOpImm, 0x2);

  static Word eval(Word rs1, Word imm) noexcept {
    return (std::bit_cast<SignedWord>(rs1) < std::bit_cast<SignedWord>(imm))
               ? 1
               : 0;
  }
};

using Slti = ArithInstruction<OpSlti, RegValueGetter<OperandKind::kRS1>,
                              ImmGetter<OperandKind::kImmI>>;

struct OpSltiu {
  static constexpr const char* kName = "sltiu";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kOpImm, 0x3);

  static Word eval(Word rs1, Word imm) noexcept { return (rs1 < imm) ? 1 : 0; }
};

using Sltiu = ArithInstruction<OpSltiu, RegValueGetter<OperandKind::kRS1>,
                               ImmGetter<OperandKind::kImmI>>;

struct OpXori {
  static constexpr const char* kName = "xori";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kOpImm, 0x4);

  static Word eval(Word rs1, Word imm) noexcept { return rs1 ^ imm; }
};

using Xori = ArithInstruction<OpXori, RegValueGetter<OperandKind::kRS1>,
                              ImmGetter<OperandKind::kImmI>>;

struct OpOri {
  static constexpr const char* kName = "ori";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kOpImm, 0x6);

  static Word eval(Word rs1, Word imm) noexcept { return rs1 | imm; }
};

using Ori = ArithInstruction<OpOri, RegValueGetter<OperandKind::kRS1>,
                             ImmGetter<OperandKind::kImmI>>;

struct OpAndi {
  static constexpr const char* kName = "andi";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kOpImm, 0x7);

  static Word eval(Word rs1, Word imm) noexcept { return rs1 & imm; }
};

using Andi = ArithInstruction<OpAndi, RegValueGetter<OperandKind::kRS1>,
                              ImmGetter<OperandKind::kImmI>>;

struct OpSlli {
  static constexpr const char* kName = "slli";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode37(RawOpcode::kOpImm, 0x1, 0x0);

  static Word eval(Word rs1, Word shamt) noexcept { return rs1 << shamt; }
};

using Slli = ArithInstruction<OpSlli, RegValueGetter<OperandKind::kRS1>,
                              ImmGetter<OperandKind::kShamt>>;

struct OpSrli {
  static constexpr const char* kName = "srli";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode37(RawOpcode::kOpImm, 0x5, 0x0);

  static Word eval(Word rs1, Word shamt) noexcept { return rs1 >> shamt; }
};

using Srli = ArithInstruction<OpSrli, RegValueGetter<OperandKind::kRS1>,
                              ImmGetter<OperandKind::kShamt>>;

struct OpSrai {
  static constexpr const char* kName = "srai";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode37(RawOpcode::kOpImm, 0x5, 0x20);

  static Word eval(Word rs1, Word shamt) noexcept {
    return std::bit_cast<Word>(std::bit_cast<SignedWord>(rs1) >> shamt);
  }
};

using Srai = ArithInstruction<OpSrai, RegValueGetter<OperandKind::kRS1>,
                              ImmGetter<OperandKind::kImmI>>;

struct OpAdd {
  static constexpr const char* kName = "add";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode37(RawOpcode::kOp, 0x0, 0x0);

  static Word eval(Word rs1, Word rs2) noexcept { return rs1 + rs2; }
};

using Add = ArithInstruction<OpAdd, RegValueGetter<OperandKind::kRS1>,
                             RegValueGetter<OperandKind::kRS2>>;

struct OpSub {
  static constexpr const char* kName = "sub";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode37(RawOpcode::kOp, 0x0, 0x20);

  static Word eval(Word rs1, Word rs2) noexcept { return rs1 - rs2; }
};

using Sub = ArithInstruction<OpSub, RegValueGetter<OperandKind::kRS1>,
                             RegValueGetter<OperandKind::kRS2>>;

struct OpSll {
  static constexpr const char* kName = "sll";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode37(RawOpcode::kOp, 0x1, 0x0);

  static Word eval(Word rs1, Word rs2) noexcept { return rs1 << (rs2 & 0x1F); }
};

using Sll = ArithInstruction<OpSll, RegValueGetter<OperandKind::kRS1>,
                             RegValueGetter<OperandKind::kRS2>>;

struct OpSlt {
  static constexpr const char* kName = "slt";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode37(RawOpcode::kOp, 0x2, 0x0);

  static Word eval(Word rs1, Word rs2) noexcept {
    return (std::bit_cast<SignedWord>(rs1) < std::bit_cast<SignedWord>(rs2))
               ? 1
               : 0;
  }
};

using Slt = ArithInstruction<OpSlt, RegValueGetter<OperandKind::kRS1>,
                             RegValueGetter<OperandKind::kRS2>>;

struct OpSltu {
  static constexpr const char* kName = "sltu";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode37(RawOpcode::kOp, 0x3, 0x0);

  static Word eval(Word rs1, Word rs2) noexcept { return (rs1 < rs2) ? 1 : 0; }
};

using Sltu = ArithInstruction<OpSltu, RegValueGetter<OperandKind::kRS1>,
                              RegValueGetter<OperandKind::kRS2>>;

struct OpXor {
  static constexpr const char* kName = "xor";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode37(RawOpcode::kOp, 0x4, 0x0);

  static Word eval(Word rs1, Word rs2) noexcept { return rs1 ^ rs2; }
};

using Xor = ArithInstruction<OpXor, RegValueGetter<OperandKind::kRS1>,
                             RegValueGetter<OperandKind::kRS2>>;

struct OpSrl {
  static constexpr const char* kName = "srl";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode37(RawOpcode::kOp, 0x5, 0x0);

  static Word eval(Word rs1, Word rs2) noexcept { return rs1 >> (rs2 & 0x1f); }
};
using Srl = ArithInstruction<OpSrl, RegValueGetter<OperandKind::kRS1>,
                             RegValueGetter<OperandKind::kRS2>>;

struct OpSra {
  static constexpr const char* kName = "sra";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode37(RawOpcode::kOp, 0x5, 0x20);

  static Word eval(Word rs1, Word rs2) noexcept {
    return std::bit_cast<Word>(std::bit_cast<SignedWord>(rs1) >> (rs2 & 0x1f));
  }
};

using Sra = ArithInstruction<OpSra, RegValueGetter<OperandKind::kRS1>,
                             RegValueGetter<OperandKind::kRS2>>;

struct OpOr {
  static constexpr const char* kName = "or";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode37(RawOpcode::kOp, 0x6, 0x0);

  static Word eval(Word rs1, Word rs2) noexcept { return rs1 | rs2; }
};

using Or = ArithInstruction<OpOr, RegValueGetter<OperandKind::kRS1>,
                            RegValueGetter<OperandKind::kRS2>>;

struct OpAnd {
  static constexpr const char* kName = "and";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode37(RawOpcode::kOp, 0x7, 0x0);

  static Word eval(Word rs1, Word rs2) noexcept { return rs1 & rs2; }
};

using And = ArithInstruction<OpAnd, RegValueGetter<OperandKind::kRS1>,
                             RegValueGetter<OperandKind::kRS2>>;
}  // namespace rv32::rv32i