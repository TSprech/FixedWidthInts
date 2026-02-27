#include <type_traits>

#include "FWILiterals.hpp"
#include "inc/FWIConcepts.hpp"

using namespace fwil::literals;

auto StronglyTypedFunction(fwic::same_as_uint8_t auto param) {
  return param;
}

int main(int argc, char* argv[]) {
  // These will cause a hard compile error if uncommented (Compiler will cite the 'throw' statement)
  {
    //    auto bin1 = 0b111111111_u8;
    //    auto oct1 = 111111_u8;
    //    auto dec1 = 257_u8;
    //    auto hex1 = 0xff01_u8;
    //    auto hex2 = 0xffff12345_u32;
  }

  {
    constexpr auto bin1 = 0b101_u64;
    constexpr auto oct1 = 0101_u64;
    constexpr auto dec1 = 101_u64;
    constexpr auto hex1 = 0xfeF1_u64;

    static_assert(bin1 == 0b101u, "xxx");
    static_assert(oct1 == 0101u, "xxx");
    static_assert(dec1 == 101u, "xxx");
    static_assert(hex1 == 0xfeF1u, "xxx");
    static_assert(std::is_same_v<const uint64_t, decltype(bin1)>, "Broken");
    static_assert(std::is_same_v<const uint64_t, decltype(oct1)>, "Broken");
    static_assert(std::is_same_v<const uint64_t, decltype(dec1)>, "Broken");
    static_assert(std::is_same_v<const uint64_t, decltype(hex1)>, "Broken");
  }

  {
    constexpr auto bin1 = 0b101_u32;
    constexpr auto oct1 = 0101_u32;
    constexpr auto dec1 = 101_u32;
    constexpr auto hex1 = 0xfeF1_u32;

    static_assert(bin1 == 0b101u, "xxx");
    static_assert(oct1 == 0101u, "xxx");
    static_assert(dec1 == 101u, "xxx");
    static_assert(hex1 == 0xfeF1u, "xxx");
    static_assert(std::is_same_v<const uint32_t, decltype(bin1)>, "Broken");
    static_assert(std::is_same_v<const uint32_t, decltype(oct1)>, "Broken");
    static_assert(std::is_same_v<const uint32_t, decltype(dec1)>, "Broken");
    static_assert(std::is_same_v<const uint32_t, decltype(hex1)>, "Broken");
  }

  {
    constexpr auto bin1 = 0b101_i64;
    constexpr auto oct1 = 0101_i64;
    constexpr auto dec1 = 101_i64;
    constexpr auto hex1 = 0xfeF1_i64;

    static_assert(bin1 == 0b101, "xxx");
    static_assert(oct1 == 0101, "xxx");
    static_assert(dec1 == 101, "xxx");
    static_assert(hex1 == 0xfeF1, "xxx");
    static_assert(std::is_same_v<const int64_t, decltype(bin1)>, "Broken");
    static_assert(std::is_same_v<const int64_t, decltype(oct1)>, "Broken");
    static_assert(std::is_same_v<const int64_t, decltype(dec1)>, "Broken");
    static_assert(std::is_same_v<const int64_t, decltype(hex1)>, "Broken");
  }

  {
    constexpr auto bin1 = 0b101_i32;
    constexpr auto oct1 = 0101_i32;
    constexpr auto dec1 = 101_i32;
    constexpr auto hex1 = 0xfeF1_i32;

    static_assert(bin1 == 0b101, "xxx");
    static_assert(oct1 == 0101, "xxx");
    static_assert(dec1 == 101, "xxx");
    static_assert(hex1 == 0xfeF1, "xxx");
    static_assert(std::is_same_v<const int32_t, decltype(bin1)>, "Broken");
    static_assert(std::is_same_v<const int32_t, decltype(oct1)>, "Broken");
    static_assert(std::is_same_v<const int32_t, decltype(dec1)>, "Broken");
    static_assert(std::is_same_v<const int32_t, decltype(hex1)>, "Broken");
  }

  {
    constexpr auto bin1 = 0b101_z;
    constexpr auto oct1 = 0101_z;
    constexpr auto dec1 = 101_z;
    constexpr auto hex1 = 0xfeF1_z;

    static_assert(bin1 == 0b101, "xxx");
    static_assert(oct1 == 0101, "xxx");
    static_assert(dec1 == 101, "xxx");
    static_assert(hex1 == 0xfeF1, "xxx");
    static_assert(std::is_same_v<const size_t, decltype(bin1)>, "Broken");
    static_assert(std::is_same_v<const size_t, decltype(oct1)>, "Broken");
    static_assert(std::is_same_v<const size_t, decltype(dec1)>, "Broken");
    static_assert(std::is_same_v<const size_t, decltype(hex1)>, "Broken");
  }

  {
    constexpr auto x8 = 100_u8;
    constexpr auto x16 = 100_u16;
    static_assert(std::is_same_v<const uint8_t, decltype(x8)>, "Broken");
    StronglyTypedFunction(8_u8);
    StronglyTypedFunction(0b1100_u8);
    StronglyTypedFunction(0xBE_u8);
    static_assert(std::is_same_v<const uint16_t, decltype(x16)>, "Broken");
  }

  return 0;
}
