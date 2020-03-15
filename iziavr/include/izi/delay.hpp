#pragma once

#include <util/delay.h>

#include <izi/mpl.hpp>
#include <izi/type_traits.hpp>

namespace izi {
namespace detail {

struct microseconds { 
  const uint16_t x;
};
struct milliseconds { 
  const uint16_t x;
};
struct seconds { 
  const uint16_t x;
};

} // namespace detail

template<typename T, enable_if_t<is_same<T, detail::microseconds>::value, int> = 0>
void delay(const T time) {
  _delay_us(time.x);
}

template<typename T, enable_if_t<is_same<T, detail::milliseconds>::value, int> = 0>
void delay(const T time) {
  _delay_ms(time.x);
}

template<typename T, enable_if_t<is_same<T, detail::seconds>::value, int> = 0>
void delay(const T time) {
  _delay_ms(1000*time.x);
}

} // namespace izi

constexpr izi::detail::microseconds operator"" _us(unsigned long long count)
{
  return izi::detail::microseconds{static_cast<uint16_t>(count)};
}

constexpr izi::detail::milliseconds operator"" _ms(unsigned long long count)
{
  return izi::detail::milliseconds{static_cast<uint16_t>(count)};
}

constexpr izi::detail::seconds operator"" _s(unsigned long long count)
{
  return izi::detail::seconds{static_cast<uint16_t>(count)};
}