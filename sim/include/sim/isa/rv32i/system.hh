// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// System instructions.

#pragma once

#include "sim/instruction_templates.hh"

namespace rv32::rv32i {

struct OpEcall {
  static constexpr std::string_view kName = "ecall";
  static inline const ExtendedOpcode extended_opcode =
      RawInstruction(0x00000000 | helpers::underlying(RawOpcode::kSystem));

  static ExecutionResult execute(SimulatorState& state) {
    return SimulatorState::ecall(state);
  }
};

using Ecall = SystemInstruction<OpEcall>;

struct OpEbreak {
  static constexpr std::string_view kName = "ebreak";
  static inline const ExtendedOpcode extended_opcode =
      RawInstruction(0x00100000 | helpers::underlying(RawOpcode::kSystem));
};

using Ebreak = UnimplementedInstruction<OpEbreak>;
}  // namespace rv32::rv32i
