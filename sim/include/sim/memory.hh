// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Memory.

#pragma once

#include <unistd.h>

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>
#include <stdexcept>
#include <type_traits>
#include <vector>

#include "boost/core/noinit_adaptor.hpp"
#include "types.hh"

namespace rv32 {

class Memory final {
 public:
  Memory() : mem_(kAddressSpaceSize) {}
  void copy(Addr dst, const void* src, Size sz) noexcept {
    assert(dst + sz <= mem_.size());
    std::memcpy(&mem_[dst], src, sz);
  }

  void copy(void* dst, Addr src, Size sz) noexcept {
    assert(src + sz <= mem_.size());
    std::memcpy(dst, &mem_[src], sz);
  }

  void memset(Addr p, Byte byte, Size sz) noexcept {
    assert(p + sz <= mem_.size());
    std::memset(&mem_[p], byte, sz);
  }

  template <typename T>
  void emit(Addr p, T value) noexcept {
    static_assert(std::is_standard_layout_v<T>);
    copy(p, std::addressof(value), sizeof(value));
  }

  template <typename T>
  T get(Addr p) {
    static_assert(std::is_standard_layout_v<T>);
    T value;
    copy(std::addressof(value), p, sizeof(value));
    return value;
  }

  // TODO: error handling
  SSize read(int fd, Addr buf, Size count) {
    assert(buf + count <= mem_.size());
    return ::read(fd, &mem_[buf], count);
  }

  // TODO: error handling
  SSize write(int fd, Addr buf, Size count) const {
    assert(buf + count <= mem_.size());
    return ::write(fd, &mem_[buf], count);
  }

  std::size_t size() const noexcept { return mem_.size(); }

 private:
  std::vector<Byte, boost::noinit_adaptor<std::allocator<Byte>>> mem_;

  static constexpr Size kAddressSpaceSize = std::numeric_limits<Addr>::max();
};
}  // namespace rv32
