#pragma once

#include <avr/interrupt.h>
#include <izi/delay.hpp>

// #define _NOP() do { __asm__ __volatile__ ("nop"); } while (0)

namespace izi {
    
class Lock
{
public:
  Lock(): _s(SREG) {
    relock();
  }

  ~Lock() {
    unlock();
  }

  void unlock() {
    SREG = _s;
  }

  void relock() {
    cli();
  }

  template<typename Cond>
  void wait(Cond cond) {
    while(cond()) { 
      unlock();
      __asm__ __volatile__ ("nop");
      cli();
    }
  }

private:
  const uint8_t _s;
};

} // namespace izi
