#pragma once

#include <bit>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace RV32::Bits {

template <typename T>
constexpr bool isPowerOfTwo(T v) {
  static_assert(std::is_integral_v<T>);
  return std::has_single_bit(v);
}

template <typename T>
constexpr bool isAligned(T v, std::size_t alignment) {
  static_assert(std::is_integral_v<T>);
  assert(isPowerOfTwo(alignment));
  return v & (alignment - 1);
}

constexpr std::uintmax_t bitMask(unsigned width) { return (1u << width) - 1u; }

template <typename T>
constexpr T bits(T v, unsigned lo, unsigned hi) {
  static_assert(std::is_integral_v<T>);
  unsigned width = hi - lo + 1;
  return (v >> lo) & bitMask(width);
}
}
