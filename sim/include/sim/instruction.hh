// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// TODO

#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include "rv32sim.hh"

namespace rv32 {

class IInstruction {
 public:
  static std::unique_ptr<IInstruction> create(RawInstruction raw_instruction);

  enum class ExecutionResult { kOk, kExit };

  virtual ExecutionResult execute(Simulator& sim) = 0;  // FIXME
  virtual std::string getName() const = 0;
  virtual ~IInstruction() {}
};
}  // namespace rv32
