#pragma once

#include "basic_instruction.hh"
#include "operands.hh"

namespace rv32 {

template <typename Op, typename... ValueGetters>
class ArithInstruction final : public BasicInstruction<Op> {
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
