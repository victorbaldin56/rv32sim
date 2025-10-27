#pragma once

#include "sim/unimplemented_instruction.hh"

namespace rv32::rv32i {

struct OpFence {
  static constexpr std::string_view kName = "fence";
  static constexpr ExtendedOpcode kExtendedOpcode = Opcode(RawOpcode::kMiscMem);
};

using Fence = UnimplementedInstruction<OpFence>;
}  // namespace rv32::rv32i
