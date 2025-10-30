// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Concrete instuction types for specialization.

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

template <typename Op, typename... ValueGetters>
class JalInstruction final : public BasicInstruction<Op> {
 public:
  ExecutionResult execute(SimulatorState& state,
                          const Operands& operands) const override {
    Addr next_pc = state.pc.getNext();
    ExecutionResult res =
        state.pc.set(Op::getNextPC(ValueGetters::get(state, operands)...));
    state.rf.set(RegNumGetter<OperandKind::kRD>::get(state, operands), next_pc);
    return res;
  }
};

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

template <typename Op>
class SystemInstruction : public BasicInstruction<Op> {
 public:
  ExecutionResult execute(SimulatorState& state,
                          const Operands& operands) const override {
    return Op::execute(state);
  }
};

template <typename Op>
class UnimplementedInstruction : public BasicInstruction<Op> {
 public:
  class Exception : public std::runtime_error {
   public:
    Exception()
        : std::runtime_error(
              std::format("Unimplemented instruction {}", Op::kName)) {}
  };

  ExecutionResult execute
      [[noreturn]] (SimulatorState& state,
                    const Operands& operand) const override {
    // attempt to execute unimplemented instruction is threated as fatal error
    throw Exception();
  }
};
}  // namespace rv32
