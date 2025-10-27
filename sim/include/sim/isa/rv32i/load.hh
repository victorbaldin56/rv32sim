#pragma once

#include "sim/basic_instruction.hh"
#include "sim/operands.hh"

namespace rv32::rv32i {

template <typename Op>
class LoadInstruction : public BasicInstruction<Op> {
 public:
  ExecutionResult execute(SimulatorState& state,
                          const Operands& operands) const override {
    using Result = Op::Result;

    Addr base = RegValueGetter<OperandKind::kRS1>::get(state, operands);
    Immediate offset = ImmGetter<OperandKind::kImmI>::get(state, operands);

    Result val = state.mem.get<Result>(base + offset);
    RegNum rd = RegNumGetter<OperandKind::kRD>::get(state, operands);
    state.rf.set(rd, val);
    ++state.pc;
    return ExecutionResult::kOk;
  }
};

struct OpLb {
  static constexpr std::string_view kName = "lb";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kLoad, 0x0);

  using Result = SignedByte;
};

using Lb = LoadInstruction<OpLb>;

struct OpLh {
  static constexpr std::string_view kName = "lh";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kLoad, 0x1);

  using Result = SignedHalf;
};

using Lh = LoadInstruction<OpLh>;

struct OpLw {
  static constexpr std::string_view kName = "lw";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kLoad, 0x2);

  using Result = SignedWord;
};

using Lw = LoadInstruction<OpLw>;

struct OpLbu {
  static constexpr std::string_view kName = "lbu";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kLoad, 0x4);

  using Result = Byte;
};

using Lbu = LoadInstruction<OpLbu>;

struct OpLhu {
  static constexpr std::string_view kName = "lhu";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kLoad, 0x5);

  using Result = Half;
};

using Lhu = LoadInstruction<OpLhu>;
}  // namespace rv32::rv32i
