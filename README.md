# CXX Sized Integer Literals & Concepts

A modern, header-only C++23 library providing safe user-defined literals for fixed-width integers and a robust suite of C++20/C++23 concepts for constraining templates against integer types and their underlying enum representations.

## Thanks
A big thanks to Steve Wilson's (swilson007) fantastic [cxx-sized-int-literals](https://github.com/swilson007/cxx-sized-int-literals) library which this library draws inspiration from. While things have changed a lot since C++14, the concept behind the utility of a library like this remains the same. If you need the functionality provided here but for C++14, 17, or 20, I recommend using the **cxx-sized-int-literals** library.

## Overview

The standard integer literal suffixes like `u`, `ul`, and `ull` suffer from portability issues similar to C++ native types like `int`, `long`, and `long long`. While `<cstdint>` provides helpful macros like `UINT64_C(<int-literal>)`, using macros for type safety is archaic and inelegant.

This library leverages C++23 `consteval` immediate functions to provide elegant, macro-free fixed-width integer suffixes (`_u8`, `_i32`, etc.) with **strict compile-time bounds checking**. Invalid literals will halt compilation.

Additionally, it bundles the `fwic` concepts namespace to constrain your templates against these fixed-width types, including safe extraction of underlying enum types without triggering eager-instantiation compiler bugs.

## Features

* **Zero Runtime Overhead:** Completely resolved at compile time.
* **Native Parsing:** Supports binary (`0b`), octal (`0`), decimal, and hexadecimal (`0x`) out of the box natively via the compiler.
* **Compile-Time Bounds Checking:** Out-of-bounds literals trigger an immediate compile error.
* **Robust Concepts:** Includes template concepts for exact matches, enum-strict matches, and flexible "enum-or-primitive" matches.
* **Eager-Instantiation Safe:** Custom type traits prevent the compiler from crashing when evaluating non-enums against underlying type concepts.

## Requirements

* A C++23 compliant compiler

---

## Part 1: Fixed-Width Integer Literals (`fwil::literals`)

### Available Suffixes

* **Unsigned:** `_u8`, `_u16`, `_u32`, `_u64`
* **Signed:** `_i8`, `_i16`, `_i32`, `_i64`
* **Size:** `_z` (Resolves to `size_t`. Note: C++23 also provides the `uz` suffix).

### Usage Example

```cpp
#include "FWILiterals.hpp"

using namespace fwil::literals;

auto u32 = 100_u32;      // uint32_t
auto u8 = 0xFF_u8;      // uint8_t (value 255)
auto u64 = 0b101_u64;    // uint64_t (value 5)
auto i8 = -50_i8;       // int8_t (value -50)
auto sz = 100_z;        // size_t

// Compile-Time Errors:
// constexpr auto bad1 = 256_u8;          // ERROR: Value out of range
// constexpr auto bad2 = 0xffff12345_u32; // ERROR: Value out of range
```

### Limitations: The Signed Minimum Value Problem

A fundamental limitation of C++ literal parsing affects the maximum negative value of signed integers. This is also documented in the **cxx-sized-int-literals** library, as it is the same challenge faced in that implementation.

Consider `int8_t`, can range from `-128` to `127`. When the compiler tokenizes `-128_i8`, it separates it into the unary minus operator (`-`) and the literal payload (`128_i8`). Because the user-defined literal receives the positive payload `128` *first*, it exceeds the maximum positive bounds (`127`) and triggers a compile error before the minus sign can be applied.

This is a compiler error due to the aforementioned limitation:

```cpp
constexpr auto x = -128_i8; // Compile error! Payload '128' exceeds int8_t max
```

**Workaround:** For the absolute minimum value of a signed integer, use `std::numeric_limits`:

```cpp
constexpr auto x = std::numeric_limits<int8_t>::min();
```

---

## Part 2: Integer & Enum Concepts (`fwic`)

The `fwic` namespace provides concepts to enforce type safety in your templates. It is specifically designed to handle the often-frustrating relationship between enums and their underlying fixed-width types.

### Concept Categories

1. **Exact Match (`same_as_*`)**: Strictly matches the primitive type.
2. **Enum Strict (`underlying_*`)**: Strictly matches an `enum` or `enum class` that has the specified underlying type.
3. **Flexible (`underlying_or_same_as_*`)**: Accepts *either* the primitive type *or* an enum with that underlying type.

Supported sizes for all categories: `uint8_t`, `uint16_t`, `uint32_t`, `uint64_t`, `int8_t`, `int16_t`, `int32_t`, `int64_t`, `size_t`, and `bool`.

### Usage Example

```cpp
#include "FWIConcepts.hpp"
#include <iostream>

// An enum backed by uint8_t
enum class DeviceStatus : uint8_t {
    OK = 0,
    FAULT = 1
};

// 1. Flexible Concept: Accepts both uint8_t AND DeviceStatus
template <fwic::underlying_or_same_as_uint8_t T>
void WriteRegister(T value) {
    // We can safely cast back to the underlying type for hardware I/O
    uint8_t raw_val = static_cast<uint8_t>(value);
    std::cout << "Writing: " << static_cast<int>(raw_val) << '\n';
}

// 2. Enum-Strict Concept: Accepts ONLY enums backed by uint16_t
template <fwic::underlying_uint16_t T>
void WriteConfig(T state) {
    // ...
}

int main() {
    uint8_t raw_byte = 0xFF;
    DeviceStatus status = DeviceStatus::OK;
    uint32_t bad_type = 100;

    WriteRegister(raw_byte);  // OK
    WriteRegister(status);    // OK
    // WriteRegister(bad_type); // COMPILE ERROR: constraint not satisfied, uin32_t type
    // WriteRegister(100); // COMPILE ERROR: constraint not satisfied, default is int type

    return 0;
}
```

### Design Notes: Safe Type Extraction

A common pitfall when writing concepts like `std::same_as<std::underlying_type_t<T>, uint8_t>` is that if `T` is *not* an enum, the compiler will attempt to eagerly instantiate `std::underlying_type_t`, hitting a standard library `static_assert` and causing a hard compile crash.

This library utilizes a custom SFINAE-friendly extraction trait (`underlying_or_self_t`) and strict `std::is_enum_v<T>` short-circuiting to guarantee that template evaluation never crashes, even when fed totally unrelated types like `std::string` or `float`.

---

## Integration

This library is strictly header-only. Simply copy `FWILiterals.hpp` and `FWIConcepts.hpp` into your project's include directory. No CMake configuration or linking is required, but a simple CMake library configuration is provided.
