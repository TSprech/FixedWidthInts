/**
 * @file FWIConcepts.hpp
 * @author TSprech
 * @date 2026/02/26
 * @brief Concept helpers that aid in writing strongly typed templates.
 * @copyright Copyright © 2026 TSprech
 * @license Apache 2.0
 */

#ifndef FWICONCEPTS_HPP
#define FWICONCEPTS_HPP

#include <concepts>
#include <cstdint>
#include <type_traits>

namespace fwic {
  // By default, just return the type itself
  template <typename T>
  struct underlying_or_self {
    using type = T;
  };

  // Specialization, if T is an enum, return its underlying type
  template <typename T>
    requires std::is_enum_v<T>
  struct underlying_or_self<T> {
    using type = std::underlying_type_t<T>;
  };

  // Helper alias for clean syntax
  template <typename T>
  using underlying_or_self_t = underlying_or_self<T>::type;

  // An int with the right sign and width
  //   Unsigned
  template <typename T>
  concept same_as_uint8_t = std::same_as<T, std::uint8_t>;
  template <typename T>
  concept same_as_uint16_t = std::same_as<T, std::uint16_t>;
  template <typename T>
  concept same_as_uint32_t = std::same_as<T, std::uint32_t>;
  template <typename T>
  concept same_as_uint64_t = std::same_as<T, std::uint64_t>;

  //   Signed
  template <typename T>
  concept same_as_int8_t = std::same_as<T, std::int8_t>;
  template <typename T>
  concept same_as_int16_t = std::same_as<T, std::int16_t>;
  template <typename T>
  concept same_as_int32_t = std::same_as<T, std::int32_t>;
  template <typename T>
  concept same_as_int64_t = std::same_as<T, std::int64_t>;

  //   Other
  template <typename T>
  concept same_as_size_t = std::same_as<T, std::size_t>;
  template <typename T>
  concept same_as_bool = std::same_as<T, bool>;

  // An enum value, and the enum is the right sign and width
  //   Unsigned
  template <typename T>
  concept underlying_uint8_t = std::is_enum_v<T> && std::same_as<std::underlying_type_t<T>, std::uint8_t>;
  template <typename T>
  concept underlying_uint16_t = std::is_enum_v<T> && std::same_as<std::underlying_type_t<T>, std::uint16_t>;
  template <typename T>
  concept underlying_uint32_t = std::is_enum_v<T> && std::same_as<std::underlying_type_t<T>, std::uint32_t>;
  template <typename T>
  concept underlying_uint64_t = std::is_enum_v<T> && std::same_as<std::underlying_type_t<T>, std::uint64_t>;

  //   Signed
  template <typename T>
  concept underlying_int8_t = std::is_enum_v<T> && std::same_as<std::underlying_type_t<T>, std::int8_t>;
  template <typename T>
  concept underlying_int16_t = std::is_enum_v<T> && std::same_as<std::underlying_type_t<T>, std::int16_t>;
  template <typename T>
  concept underlying_int32_t = std::is_enum_v<T> && std::same_as<std::underlying_type_t<T>, std::int32_t>;
  template <typename T>
  concept underlying_int64_t = std::is_enum_v<T> && std::same_as<std::underlying_type_t<T>, std::int64_t>;

  //   Other
  template <typename T>
  concept underlying_size_t = std::is_enum_v<T> && std::same_as<std::underlying_type_t<T>, std::size_t>;
  template <typename T>
  concept underlying_bool = std::is_enum_v<T> && std::same_as<std::underlying_type_t<T>, bool>;

  // An int with the right sign and width, or an enum value, and the enum is the right size and width
  //   Unsigned
  template <typename T>
  concept underlying_or_same_as_uint8_t = std::same_as<underlying_or_self_t<T>, std::uint8_t>;
  template <typename T>
  concept underlying_or_same_as_uint16_t = std::same_as<underlying_or_self_t<T>, std::uint16_t>;
  template <typename T>
  concept underlying_or_same_as_uint32_t = std::same_as<underlying_or_self_t<T>, std::uint32_t>;
  template <typename T>
  concept underlying_or_same_as_uint64_t = std::same_as<underlying_or_self_t<T>, std::uint64_t>;

  //   Signed
  template <typename T>
  concept underlying_or_same_as_int8_t = std::same_as<underlying_or_self_t<T>, std::int8_t>;
  template <typename T>
  concept underlying_or_same_as_int16_t = std::same_as<underlying_or_self_t<T>, std::int16_t>;
  template <typename T>
  concept underlying_or_same_as_int32_t = std::same_as<underlying_or_self_t<T>, std::int32_t>;
  template <typename T>
  concept underlying_or_same_as_int64_t = std::same_as<underlying_or_self_t<T>, std::int64_t>;

  //   Other
  template <typename T>
  concept underlying_or_same_as_size_t = std::same_as<underlying_or_self_t<T>, std::size_t>;
  template <typename T>
  concept underlying_or_same_as_bool = std::same_as<underlying_or_self_t<T>, bool>;
}  // namespace intc

#endif  // FWICONCEPTS_HPP
