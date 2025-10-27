#pragma once

#include "instruction.hh"

namespace rv32 {

template <typename Op>
class BasicInstruction : public IInstruction {
 public:
  constexpr std::string_view getName() const noexcept override {
    return Op::kName;
  }

  constexpr ExtendedOpcode getExtendedOpcode() const noexcept override {
    return Op::kExtendedOpcode;
  }
};

template <typename Op, typename... ValueGetters>
class ArithInstruction : public BasicInstruction<Op> {
 public:
  ExecutionResult execute(SimulatorState& state,
                          const Operands& operands) const override {
    state.rf.set(RegNumGetter<OperandKind::kRD>::get(state, operands),
                 Op::eval(ValueGetters::get(state, operands)...));
    ++state.pc;
    return ExecutionResult::kOk;
  }
};
}  // namespace rv32
