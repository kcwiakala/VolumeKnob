#pragma once

#include <avr/io.h>

#include <izi/bitmask.hpp>

namespace izi {

struct InterruptHandler
{
  virtual void isr() = 0;
  InterruptHandler* _next = nullptr;
};

namespace isr {

#ifdef PCIE0
struct pcint0 
{
  template<typename BitMask>
  static void setup() {
    BitMask::assign(PCMSK0);
  }

  static void enable(const bool enabled) {
    izi::bitmask<PCIE0>::set(PCICR, enabled);
  }

  static void attach(InterruptHandler& handler);
};
#endif

#ifdef PCIE1
struct pcint1
{
  template<typename BitMask>
  static void setup() {
    BitMask::assign(PCMSK1);
  }

  static void enable(const bool enabled) {
    izi::bitmask<PCIE1>::set(PCICR, enabled);
  }

  static void attach(InterruptHandler& handler);
};
#endif

#ifdef PCIE2
struct pcint2
{
  template<typename BitMask>
  static void setup() {
    BitMask::assign(PCMSK2);
  }

  static void enable(const bool enabled) {
    izi::bitmask<PCIE2>::set(PCICR, enabled);
  }

  static void attach(InterruptHandler& handler);
};
#endif

} // namespace isr
} // namespace izi