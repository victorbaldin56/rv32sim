// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// TODO

#pragma once

#include <string_view>

#include "opcodes.hh"
#include "operands.hh"
#include "state.hh"

namespace rv32 {

class IInstruction {
 public:
  virtual ExecutionResult execute(SimulatorState& sim,
                                  const Operands& ops) const = 0;
  virtual constexpr std::string_view getName() const noexcept = 0;
  virtual constexpr ExtendedOpcode getExtendedOpcode() const noexcept = 0;
  virtual ~IInstruction() {}
};
}  // namespace rv32
