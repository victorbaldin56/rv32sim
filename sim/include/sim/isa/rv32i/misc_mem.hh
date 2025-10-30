// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// MISC MEM instructions.

#pragma once

#include "sim/instruction_templates.hh"

namespace rv32::rv32i {

struct OpFence {
  static constexpr std::string_view kName = "fence";
  static constexpr ExtendedOpcode kExtendedOpcode = Opcode(RawOpcode::kMiscMem);
};

using Fence = UnimplementedInstruction<OpFence>;
}  // namespace rv32::rv32i
