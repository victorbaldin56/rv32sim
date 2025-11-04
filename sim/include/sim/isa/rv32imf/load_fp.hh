// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Load instructions for floating point.

#pragma once

#include "sim/instruction_templates.hh"

namespace rv32::rv32imf {

struct OpFlw {
  static constexpr std::string_view kName = "flw";
  static constexpr ExtendedOpcode kExtendedOpcode = Opcode(RawOpcode::kLoadFp);

  using Result = float;
};

using Flw = LoadInstruction<OpFlw>;
}
