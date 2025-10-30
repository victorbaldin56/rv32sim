// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Register file.

#pragma once

#include <array>
#include <boost/algorithm/string.hpp>
#include <magic_enum/magic_enum.hpp>
#include <string>

#include "base/helpers.hh"
#include "config.hh"
#include "memory.hh"

namespace rv32 {

class RegisterFile {
 public:
  // clang-format off
  enum class Register : std::size_t {
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

  static auto getRegName(Register num) noexcept {
    auto name = magic_enum::enum_name(num);

    // a price of codestyle...
    std::string transformed_name(name.substr(1));
    return boost::algorithm::to_lower_copy(transformed_name);
  }

  static auto getRegName(std::size_t num) noexcept {
    return getRegName(static_cast<Register>(num));
  }

  Word get(std::size_t num) const noexcept { return regs_[num]; }
  Word get(Register num) const noexcept {
    return get(helpers::underlying(num));
  }

  void set(std::size_t num, Word value) noexcept {
    if (num == helpers::underlying(Register::kZero)) {
      return;
    }
    regs_[num] = value;
  }

  void set(Register num, Word value) noexcept {
    return set(helpers::underlying(num), value);
  }

 private:
  std::array<Word, helpers::underlying(Register::kNumRegisters)> regs_ = {};
};
}  // namespace rv32
