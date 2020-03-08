#pragma once

#include <stdint.h>
#include <stdlib.h>

#include <izi/interrupt.hpp>

namespace izi {

template<class Clk, class Data, class Isr>
class Encoder: public InterruptHandler<Isr>
{
  static_assert(Clk::size == 1, "Invalid Clk port size");
  static_assert(Data::size == 1, "Invalid Clk port size");

public:
  Encoder(const bool pullup = true) {
    Clk::setup(false, pullup);
    Data::setup(false, pullup);
  }

  int8_t read()
  {
    const int8_t d = delta;
    delta = 0;
    return d;
  }

private:
  void isr() override
  {
    delta += (Clk::any() ^ Data::any()) ? 1 : -1;
  }

private:
  int8_t delta = 0;
};

} // namespace izi