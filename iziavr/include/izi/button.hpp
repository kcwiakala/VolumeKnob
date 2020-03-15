#pragma once

#include <izi/interrupt.hpp>

namespace izi {
  
template<typename Pin, bool ActiveState = false>
class InterruptButton: public InterruptHandler
{
public:
  using pin_t = Pin;
  
  InterruptButton(bool pullup = true)
  {
    Pin::setup(false, pullup);
  }

  bool clicked() {
    const bool aux = _clicked;
    _clicked = false;
    return aux;
  }

private:
  void isr() override {
    _clicked = ActiveState ? Pin::all() : Pin::none();
  }

private:
  bool _clicked = false;
};

template<typename Pin, bool ActiveState = false>
class PolledButton
{
public:
  using pin_t = Pin;
  
  PolledButton(bool pullup = true)
  {
    Pin::setup(false, pullup);
  }

  bool clicked() {
    if(_state != ActiveState ? Pin::none() : Pin::all()) {
      _state = !_state;
      return _state;
    }
    return false;
  }

private:
  bool _state = !ActiveState;
};

} // namespace izi 
