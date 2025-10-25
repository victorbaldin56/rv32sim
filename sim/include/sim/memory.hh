// See LICENSE for license details.

// rv32sim - a simple RV32 simulator
//
// Memory.

#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>
#include <stdexcept>
#include <vector>

#include "types.hh"

namespace RV32 {

class Memory final {
 public:
  Memory() : mem_(kAddressSpaceSize) {}
  void copy(Addr dst, const void* src, Size sz) noexcept {
    assert(dst + sz <= mem_.size());
    std::memcpy(&mem_[dst], src, sz);
  }

  void memset(Addr p, Byte byte, Size sz) noexcept {
    assert(p + sz <= mem_.size());
    std::memset(&mem_[p], byte, sz);
  }

  template <typename T>
  void emit(Addr p, T value) noexcept {
    copy(p, &value, sizeof(value));
  }

 private:
  std::vector<Byte> mem_;

  static constexpr Size kAddressSpaceSize = std::numeric_limits<Addr>::max();
};
}  // namespace RV32
