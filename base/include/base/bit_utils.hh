// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Common bit manipulation.

#pragma once

#include <bit>
#include <cassert>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace rv32::bits {

template <typename T>
constexpr bool isPowerOfTwo(T v) noexcept {
  static_assert(std::is_integral_v<T>);
  return std::has_single_bit(v);
}

template <typename T>
constexpr bool isAligned(T v, std::size_t alignment) noexcept {
  static_assert(std::is_integral_v<T>);
  assert(isPowerOfTwo(alignment));
  return !(v & (alignment - 1));
}

template <typename T>
constexpr T alignDown(T v, std::size_t alignment) noexcept {
  static_assert(std::is_integral_v<T>);
  assert(isPowerOfTwo(alignment));
  return v & ~(alignment - 1);
}

template <typename T>
constexpr T bitMask(unsigned width = sizeof(T) * CHAR_BIT) {
  return (static_cast<T>(1) << width) - 1;
}

template <typename T>
constexpr T extractBits(T v, unsigned lo, unsigned hi) noexcept {
  static_assert(std::is_integral_v<T>);
  unsigned width = hi - lo + 1;
  return (v >> lo) & bitMask<T>(width);
}

template <typename U>
constexpr auto signExtend(U x, unsigned width) noexcept {
  static_assert(std::is_unsigned_v<U>);
  using Signed = std::make_signed_t<U>;
  unsigned shift = sizeof(U) * CHAR_BIT - width;
  return static_cast<Signed>(static_cast<Signed>(x << shift) >> shift);
}
}  // namespace rv32::bits
