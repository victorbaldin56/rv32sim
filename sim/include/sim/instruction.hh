// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// TODO

#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include "state.hh"

namespace rv32 {

class IInstruction {
 public:
  enum class ExecutionResult { kOk, kExit };

  virtual ExecutionResult execute(SimulatorState& sim) const = 0;  // FIXME
  virtual std::string getName() const = 0;
  virtual ~IInstruction() {}
};
}  // namespace rv32
