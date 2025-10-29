#pragma once

#include "sim/instruction_templates.hh"

namespace rv32::rv32i {

struct OpEcall {
  static constexpr std::string_view kName = "ecall";
  static constexpr ExtendedOpcode kExtendedOpcode =
      RawInstruction(0x00000000 | helpers::underlying(RawOpcode::kSystem));

  static ExecutionResult execute(SimulatorState& state) {
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
