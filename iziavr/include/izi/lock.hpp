#pragma once

#include <avr/interrupt.h>

namespace izi {
    
class Lock
{
public:
  Lock(): _s(SREG) {
    cli();
  }

  ~Lock() {
    SREG = _s;
  }

private:
  const uint8_t _s;
};

} // namespace izi
