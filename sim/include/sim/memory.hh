// See LICENSE for license details.

// rv32sim - a simple RV32 simulator
//
// Memory.

#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <vector>

namespace RV32 {

class Memory final {
 public:
  using Size_t = std::uint32_t;
  using Addr_t = std::uint32_t;

  Memory() : mem_(kMemorySize) {}
  void load(Addr_t dst, const void* src, Size_t sz) noexcept {
    assert(dst + sz <= mem_.size());
    std::memcpy(&mem_[dst], src, sz);
  }

 private:
  std::vector<std::uint8_t> mem_;

  static constexpr Size_t kMemorySize = 0xffffffff;
};
}  // namespace RV32
