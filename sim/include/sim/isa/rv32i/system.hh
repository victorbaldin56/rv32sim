#pragma once

#include "sim/unimplemented_instruction.hh"

namespace rv32::rv32i {

template <typename Op>
class SystemInstruction : public BasicInstruction<Op> {
 public:
  ExecutionResult execute(SimulatorState& state,
                          const Operands& operands) const override {
    return Op::execute(state);
  }
};

struct OpEcall {
  static constexpr std::string_view kName = "ecall";
  static constexpr ExtendedOpcode kExtendedOpcode =
      RawInstruction(0x00000000 | helpers::underlying(RawOpcode::kSystem));

  ExecutionResult execute(SimulatorState& state) {
    return SimulatorState::ecall(state);
  }
};

using Ecall = SystemInstruction<OpEcall>;

struct OpEbreak {
  static constexpr std::string_view kName = "ebreak";
  static constexpr ExtendedOpcode kExtendedOpcode =
      RawInstruction(0x00100000 | helpers::underlying(RawOpcode::kSystem));
};

using Ebreak = UnimplementedInstruction<OpEbreak>;
}  // namespace rv32::rv32i
