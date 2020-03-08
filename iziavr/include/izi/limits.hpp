#pragma once

#include <izi/type_traits.hpp>

namespace izi {
namespace detail {

template<typename T, bool B> struct MaxValue 
{ 
  static constexpr T value = T(-1); 
};

template<typename T> struct MaxValue<T, true> 
{ 
  static constexpr T value = T(-1) & ~(T(1) << (8*sizeof(T)-1)); ; 
};

} // namespace detail

template<typename T>
struct numeric_limits
{
  static constexpr T max = detail::MaxValue<T, is_signed<T>::value>::value;
  static constexpr T min = max + 1;
};

} // namespace izi