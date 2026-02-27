/**
 * @file FWIConcepts.hpp
 * @author TSprech
 * @date 2026/02/26
 * @brief Concept helpers that aid in writing strongly typed templates.
 * @copyright Copyright © 2026 TSprech
 * @license Apache 2.0
 */

#ifndef FWILITERALS_HPP
#define FWILITERALS_HPP

#include <cstddef>
#include <cstdint>
#include <limits>
#include <stdexcept>

// Macro to define the literal suffixes and perform the compile time bounds checking
#define FIXED_WIDTH_INT_LITERALS_SUFFIX(suffix, type_name)                              \
  consteval type_name operator""##suffix(unsigned long long val) {                      \
    if (val > static_cast<unsigned long long>(std::numeric_limits<type_name>::max())) { \
      throw std::out_of_range("Literal value out of range for type: " #type_name);      \
    }                                                                                   \
    return static_cast<type_name>(val);                                                 \
  }

namespace fwil::literals {
  // clang-format off
    // Unsigned
    FIXED_WIDTH_INT_LITERALS_SUFFIX(_u8,  std::uint8_t)
    FIXED_WIDTH_INT_LITERALS_SUFFIX(_u16, std::uint16_t)
    FIXED_WIDTH_INT_LITERALS_SUFFIX(_u32, std::uint32_t)
    FIXED_WIDTH_INT_LITERALS_SUFFIX(_u64, std::uint64_t)
    // Signed
    FIXED_WIDTH_INT_LITERALS_SUFFIX(_i8,  std::int8_t)
    FIXED_WIDTH_INT_LITERALS_SUFFIX(_i16, std::int16_t)
    FIXED_WIDTH_INT_LITERALS_SUFFIX(_i32, std::int32_t)
    FIXED_WIDTH_INT_LITERALS_SUFFIX(_i64, std::int64_t)
    // Other
    FIXED_WIDTH_INT_LITERALS_SUFFIX(_z,   std::size_t)
  // clang-format on
}  // namespace fixed_width_int_literals::literals

#undef FIXED_WIDTH_INT_LITERALS_SUFFIX

#endif  // FWILITERALS_HPP
