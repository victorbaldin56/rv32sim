#pragma once

#include "instruction.hh"

namespace rv32 {

template <typename Op>
class ArithInstruction : public IInstruction {
 public:
  const char* getName() const noexcept override { return Op::kName; }
  ExtendedOpcode getExtendedOpcode() const noexcept override {
    return Op::kExtendedOpcode;
  }
};
}  // namespace rv32
