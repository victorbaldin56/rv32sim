#pragma once

#include <tuple>
#include <type_traits>
#include <variant>

namespace rv32::helpers {

template <typename E>
constexpr typename std::underlying_type<E>::type underlying(E e) noexcept {
  return static_cast<typename std::underlying_type<E>::type>(e);
}

// some magic to make variant type from some variable length template
template <typename S>
struct ToVariant;

template <typename... Types>
struct ToVariant<std::tuple<Types...>> {
  using Type = std::variant<Types...>;
};

template <typename S>
using ToVariantT = ToVariant<S>::Type;
}  // namespace rv32::helpers
