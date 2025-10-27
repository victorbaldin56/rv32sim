#pragma once

#include "sim/basic_instruction.hh"
#include "sim/operands.hh"

namespace rv32::rv32i {

template <typename Op>
class StoreInstruction : public BasicInstruction<Op> {
 public:
  ExecutionResult execute(SimulatorState& state,
                          const Operands& operands) const override {
    using Emitted = Op::Emitted;

    Addr base = RegValueGetter<OperandKind::kRS1>::get(state, operands);
    Immediate offset = ImmGetter<OperandKind::kImmS>::get(state, operands);

    Emitted val = RegValueGetter<OperandKind::kRS2>::get(state, operands);
    state.mem.emit(base + offset, val);
    ++state.pc;
    return ExecutionResult::kOk;
  }
};

struct OpSb {
  static constexpr std::string_view kName = "sb";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kStore, 0x0);

  using Emitted = Byte;
};

using Sb = StoreInstruction<OpSb>;

struct OpSh {
  static constexpr std::string_view kName = "sh";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kStore, 0x1);

  using Emitted = Half;
};

using Sh = StoreInstruction<OpSh>;

struct OpSw {
  static constexpr std::string_view kName = "sw";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kStore, 0x2);

  using Emitted = Word;
};

using Sw = StoreInstruction<OpSw>;
}  // namespace rv32::rv32i
