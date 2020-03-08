#pragma once

#include <izi/traits/port.hpp>
#include <izi/utils/bitmask.hpp>

namespace izi {
namespace details {

template<typename Traits, int ...bits>
struct Port
{
  using bitmask_t = utils::bitmask<bits...>;
  static constexpr uint8_t mask = bitmask_t::mask;
  static constexpr uint8_t size = sizeof...(bits);
  using traits_type = Traits;
  
  Port(const bool output = true, const bool pullup = false) 
  {
    setup(output, pullup);
  }

  static void setup(const bool output, const bool pullup = false)
  {
    if(output) {
      Traits::output(mask);
    } else {
      Traits::input(mask);
    }
    set(pullup);
  }

  static void set(const bool value)
  {
    if(value) {
      Traits::set(mask);
    } else {
      Traits::clear(mask);
    }
  }

  static void toggle() 
  {
    Traits::toggle(mask);
  }

  static uint8_t get()
  {
    return Traits::get(mask);
  }

  static bool any()
  {
    return get() != 0;
  }

  static bool all()
  {
    return get() == mask;
  }

  static uint8_t collapsed()
  {
    return bitmask_t::collapse(get());
  }
};

} // namespace details

template<int ... bits> 
using PortA = details::Port<traits::A, bits...>;

template<int ... bits> 
using PortB = details::Port<traits::B, bits...>;

template<int ... bits> 
using PortC = details::Port<traits::C, bits...>;

template<int ... bits> 
using PortD = details::Port<traits::D, bits...>;

} // namespace izi