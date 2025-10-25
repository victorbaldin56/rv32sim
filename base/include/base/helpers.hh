#pragma once

#include <type_traits>

namespace RV32::Helpers {

template <typename E>
constexpr typename std::underlying_type<E>::type underlying(E e) noexcept {
  return static_cast<typename std::underlying_type<E>::type>(e);
}
}
