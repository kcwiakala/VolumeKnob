#pragma once

namespace izi {
namespace utils {

template<int ... bits> struct bitmask;

template<int b>
struct bitmask<b>
{
  static_assert(b<8, "Only 8-bit masks are supported");
  
  static constexpr uint8_t mask = (1 << b);
  static constexpr uint8_t size = 1;
  
  static uint8_t collapse(uint8_t value)
  {
    return (value >> b) & 0x01;
  }
};

template<int b, int ... bits>
struct bitmask<b, bits...>
{
  static constexpr uint8_t mask = (1 << b) | bitmask<bits...>::mask;
  static constexpr uint8_t size = 1 + bitmask<bits...>::size;

  static uint8_t collapse(uint8_t value)
  {
    return bitmask<b>::collapse(value) | (bitmask<bits...>::collapse(value) << sizeof...(bits));
  }
};

} // namespace utils
} // namespace izi