#pragma once

#include <izi/traits/port.hpp>
#include <izi/bitmask.hpp>

namespace izi {
namespace detail {

template<class p1, class p2> struct port_merge;

template<typename Traits, int ...bits>
struct Port: izi::bitmask<bits...>
{
  using self_t = Port<Traits, bits...>;
  using bitmask_t = izi::bitmask<bits...>;
  static constexpr uint8_t mask = bitmask_t::mask;
  static constexpr uint8_t size = sizeof...(bits);
  using traits_type = Traits;
  
  template<typename other>
  using merge = port_merge<self_t, other>;

  Port(const bool output = true, const bool pullup = false) 
  {
    setup(output, pullup);
  }

  static void setup(const bool output, const bool pullup = false)
  {
    bitmask_t::set(Traits::ddr(), output);
    set(pullup);
  }

  static void set(const bool value)
  {
    bitmask_t::set(Traits::port(), value);
  }

  static void toggle() 
  {
    bitmask_t::toggle(Traits::port());
  }

  static uint8_t get()
  {
    return bitmask_t::get(Traits::pin());
  }

  static bool any()
  {
    return get() != 0;
  }

  static bool all()
  {
    return get() == mask;
  }

  static uint8_t count()
  {
    return __builtin_popcount(get());
  }

  static bool none()
  {
    return get() == 0;
  }

  static uint8_t collapsed()
  {
    return bitmask_t::collapse(get());
  }
};

template<typename Traits, int ... b1, int ... b2>
struct port_merge<Port<Traits, b1...>, Port<Traits, b2...> >: Port<Traits, b1..., b2...> { };

} // namespace detail

template<int ... bits> 
using PortA = detail::Port<traits::PortA, bits...>;

template<int ... bits> 
using PortB = detail::Port<traits::PortB, bits...>;

template<int ... bits> 
using PortC = detail::Port<traits::PortC, bits...>;

template<int ... bits> 
using PortD = detail::Port<traits::PortD, bits...>;

} // namespace izi