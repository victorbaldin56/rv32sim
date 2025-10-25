// See LICENSE for license details.

// rv32sim - a simple RV32 simulator
//
// Virtual CPU.

#pragma once

#include <array>

#include "base/helpers.hh"
#include "config.hh"
#include "memory.hh"

namespace RV32 {

class RegisterFile {
 public:
  // clang-format off
  enum class Registers : std::size_t {
    kZero =  0,
    kRA   =  1,
    kSP   =  2,
    kGP   =  3,
    kTP   =  4,
    kT0   =  5, kT1, kT2,
    kFP   =  8,
    kS0   =  8, kS1,
    kA0   = 10, kA1, kA2, kA3, kA4, kA5, kA6, kA7,
    kS2   = 18, kS3, kS4, kS5, kS6, kS7, kS8, kS9, kS10, kS11,
    kT3   = 28, kT4, kT5, kT6,

    kNumRegisters
  };
  // clang-format on

  Word get(std::size_t num) const noexcept { return regs_[num]; }
  void set(std::size_t num, Word value) noexcept { regs_[num] = value; }

 private:
  std::array<Word, Helpers::underlying(Registers::kNumRegisters)> regs_;
};
}
