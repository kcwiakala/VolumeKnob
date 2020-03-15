#pragma once

#include <stdint.h>
#include <stdlib.h>

#include <izi/interrupt.hpp>

namespace izi {

template<class Clk, class Data>
class Encoder: public InterruptHandler
{
  static_assert(Clk::size == 1, "Invalid Clk port size");
  static_assert(Data::size == 1, "Invalid Clk port size");

public:
  using clk_t = Clk;
  using dt_t = Data;

  Encoder(const bool pullup = true) {
    Clk::setup(false, pullup);
    Data::setup(false, pullup);
    _clk = Clk::any();
  }

  int8_t delta()
  {
    const int8_t aux = _delta;
    _delta = 0;
    return aux;
  }

private:
  void isr() override
  {
    const uint8_t clk = Clk::any();
    if(clk != _clk) {
      _delta = (clk != Data::any()) ? 1 : -1;
      _clk = clk;
    }
  }

private:
  bool _clk;
  int8_t _delta = 0;
};

} // namespace izi