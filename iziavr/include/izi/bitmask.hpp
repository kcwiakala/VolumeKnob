#pragma once

#include <stdint.h>

namespace izi {

template<int ... bits> struct bitmask;

namespace detail {

template<typename Derived>
struct bitmask
{
  template<typename T>
  static void assign(T& v) {
    v = Derived::mask;
  }

  template<typename T>
  static void set(T& v, const bool enabled = true) {
    if(enabled) {
      v |= Derived::mask;
    } else {
      v &= ~Derived::mask;
    }    
  }

  template<typename T>
  static void toggle(T& v) {
    v ^= Derived::mask;
  }

  template<typename T>
  static uint8_t get(T& v) {
    return v & Derived::mask;
  }
};

template<class bm1, class bm2> struct bitmask_merge;
template<int ... b1, int ... b2>
struct bitmask_merge<izi::bitmask<b1...>, izi::bitmask<b2...> >: izi::bitmask<b1..., b2...> {};

} // namespace detail

template<int b>
struct bitmask<b>: detail::bitmask< bitmask<b> >
{
  static_assert(b<8, "Only 8-bit masks are supported");
 
  using self_t = bitmask<b>;

  static constexpr uint8_t mask = (1 << b);
  static constexpr uint8_t size = 1;
  
  static uint8_t collapse(uint8_t value)
  {
    return (value >> b) & 0x01;
  }

  template<typename other>
  using merge = detail::bitmask_merge<self_t, other>;
};

template<int b, int ... bits>
struct bitmask<b, bits...>: detail::bitmask< bitmask<b, bits...> >
{
  using self_t = bitmask<b, bits...>;

  static constexpr uint8_t mask = (1 << b) | bitmask<bits...>::mask;
  static constexpr uint8_t size = 1 + bitmask<bits...>::size;

  static uint8_t collapse(uint8_t value)
  {
    return bitmask<b>::collapse(value) | (bitmask<bits...>::collapse(value) << sizeof...(bits));
  }

  template<typename other>
  using merge = detail::bitmask_merge<self_t, other>;
};

} // namespace izi

constexpr uint8_t operator"" _bv(unsigned long long bit)
{
    return 1 << bit;
}
