// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Store instructions for floating point.

#pragma once

#include "sim/instruction_templates.hh"

namespace rv32::rv32imf {

struct OpFsw {
  static constexpr std::string_view kName = "fsw";
  static inline const ExtendedOpcode extended_opcode =
      Opcode(RawOpcode::kStoreFp);

  using Emitted = float;
};

using Fsw = StoreInstruction<OpFsw>;
}
