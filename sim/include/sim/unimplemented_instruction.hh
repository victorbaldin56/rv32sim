#pragma once

#include <format>

#include "basic_instruction.hh"

namespace rv32 {

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
