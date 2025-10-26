#pragma once

#include <bit>
#include <cassert>
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
  return v & (alignment - 1);
}

constexpr std::uintmax_t bitMask(unsigned width) { return (1u << width) - 1u; }

template <typename T>
constexpr T extractBits(T v, unsigned lo, unsigned hi) noexcept {
  static_assert(std::is_integral_v<T>);
  unsigned width = hi - lo + 1;
  return (v >> lo) & bitMask(width);
}

template <typename U>
constexpr auto signExtend(U x, unsigned width) noexcept {
  static_assert(std::is_unsigned_v<U>);
  using T = std::make_signed_t<U>;
  unsigned shift = sizeof(U) - width;
  return static_cast<T>(static_cast<T>(x << shift) >> shift);
}
}  // namespace rv32::bits
