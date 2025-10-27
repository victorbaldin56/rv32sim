#pragma once

#include "instruction.hh"

namespace rv32 {

template <typename Op>
class BasicInstruction : public IInstruction {
 public:
  constexpr std::string_view getName() const noexcept override {
    return Op::kName;
  }

  constexpr ExtendedOpcode getExtendedOpcode() const noexcept override {
    return Op::kExtendedOpcode;
  }
};
}  // namespace rv32
