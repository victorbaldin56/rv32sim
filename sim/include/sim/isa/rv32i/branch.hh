#pragma once

#include "sim/basic_instruction.hh"
#include "sim/operands.hh"

namespace rv32::rv32i {

template <typename Op>
class BranchInstruction final : public BasicInstruction<Op> {
 public:
  ExecutionResult execute(SimulatorState& state,
                          const Operands& operands) const override {
    if (Op::compare(RegValueGetter<OperandKind::kRS1>::get(state, operands),
                    RegValueGetter<OperandKind::kRS2>::get(state, operands))) {
      return state.pc.set(state.pc.get() +
                          ImmGetter<OperandKind::kImmB>::get(state, operands));
    }
    ++state.pc;
    return ExecutionResult::kOk;
  }
};

struct OpBeq {
  static constexpr std::string_view kName = "beq";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kBranch, 0x0);

  static bool compare(Word lhs, Word rhs) noexcept { return lhs == rhs; }
};

using Beq = BranchInstruction<OpBeq>;

struct OpBne {
  static constexpr std::string_view kName = "bne";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kBranch, 0x1);

  static bool compare(Word lhs, Word rhs) noexcept { return lhs != rhs; }
};

using Bne = BranchInstruction<OpBne>;

struct OpBlt {
  static constexpr std::string_view kName = "blt";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kBranch, 0x4);

  static bool compare(Word lhs, Word rhs) noexcept {
    return std::bit_cast<SignedWord>(lhs) < std::bit_cast<SignedWord>(rhs);
  }
};

using Blt = BranchInstruction<OpBlt>;

struct OpBge {
  static constexpr std::string_view kName = "bge";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kBranch, 0x5);

  static bool compare(Word lhs, Word rhs) noexcept {
    return std::bit_cast<SignedWord>(lhs) >= std::bit_cast<SignedWord>(rhs);
  }
};

using Bge = BranchInstruction<OpBge>;

struct OpBltu {
  static constexpr std::string_view kName = "bltu";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kBranch, 0x6);

  static bool compare(Word lhs, Word rhs) noexcept { return lhs < rhs; }
};

using Bltu = BranchInstruction<OpBltu>;

struct OpBgeu {
  static constexpr std::string_view kName = "bgeu";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kBranch, 0x7);

  static bool compare(Word lhs, Word rhs) noexcept { return lhs >= rhs; }
};

using Bgeu = BranchInstruction<OpBgeu>;
}  // namespace rv32::rv32i
