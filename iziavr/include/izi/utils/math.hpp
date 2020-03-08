#pragma once

#include <stdint.h>
#include <izi/limits.hpp>

namespace izi {
namespace utils {
namespace detail {

template<uint8_t Count, uint8_t Base, unsigned long Value>
struct digits
{
  static constexpr uint8_t count = digits<1+Count, Base, Value/Base>::count;
};

template<uint8_t Count, uint8_t Base>
struct digits<Count, Base, 0>
{
  static constexpr uint8_t count = Count;
};

template<uint8_t Base, uint8_t Exp, unsigned long Value>
struct pow
{
  static constexpr unsigned long value = pow<Base, Exp-1, 10*Value>::value;
};

template<uint8_t Base, unsigned long Value>
struct pow<Base, 0, Value>
{
  static constexpr unsigned long value = Value;
};

} // namespace detail

template<typename T>
struct digits
{
  static constexpr uint8_t dec = detail::digits<0,10,numeric_limits<T>::max>::count;
  static constexpr uint8_t oct = detail::digits<0, 8,numeric_limits<T>::max>::count;
  static constexpr uint8_t hex = 2*sizeof(T);
  static constexpr uint8_t bin = 8*sizeof(T);
};

template<uint8_t Base, uint8_t Exp>
struct pow
{
  static constexpr unsigned long value = detail::pow<Base, Exp, 1>::value;
};

} // namespace utils
} // namespace izi