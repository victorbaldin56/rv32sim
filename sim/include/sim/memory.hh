// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Memory.

#pragma once

#include <unistd.h>

#include <boost/core/noinit_adaptor.hpp>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>
#include <stdexcept>
#include <type_traits>
#include <vector>

#include "base/mmaped_file.hh"
#include "types.hh"

namespace rv32 {

class Memory final {
 public:
  Memory()
      : mem_(makeUniqueMmap(nullptr, kAddressSpaceSize, PROT_WRITE,
                            MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)) {}

  Size size() const noexcept { return mem_.get_deleter().len; }

  void copy(Addr dst, const void* src, Size sz) noexcept {
    assert(dst + sz <= size());
    std::memcpy(&operator[](dst), src, sz);
  }

  void copy(void* dst, Addr src, Size sz) noexcept {
    assert(src + sz <= size());
    std::memcpy(dst, &operator[](src), sz);
  }

  void memset(Addr p, Byte byte, Size sz) noexcept {
    assert(p + sz <= size());
    std::memset(&operator[](p), byte, sz);
  }

  template <typename T>
  void emit(Addr p, T value) noexcept {
    static_assert(std::is_trivially_copyable_v<T>);
    copy(p, std::addressof(value), sizeof(value));
  }

  template <typename T>
  T get(Addr p) {
    static_assert(std::is_trivially_copyable_v<T>);
    T value;
    copy(std::addressof(value), p, sizeof(value));
    return value;
  }

  // TODO: error handling
  SSize read(int fd, Addr buf, Size count) {
    assert(buf + count <= size());
    return ::read(fd, &operator[](buf), count);
  }

  // TODO: error handling
  SSize write(int fd, Addr buf, Size count) const {
    assert(buf + count <= size());
    return ::write(fd, &operator[](buf), count);
  }

 private:
  UniqueMmap mem_;

  Byte* data() const noexcept { return static_cast<Byte*>(mem_.get()); }
  Byte& operator[](Size n) { return data()[n]; }
  const Byte& operator[](Size n) const { return data()[n]; }

  static constexpr Size kAddressSpaceSize =
      0x80000000;  // we dont need 4 GB because in absence of kernel space.
};
}  // namespace rv32
