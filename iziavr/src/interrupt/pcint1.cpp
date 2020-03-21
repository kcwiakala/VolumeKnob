#include <avr/interrupt.h>
#include <izi/interrupt.hpp>

#ifdef PCMSK1

static izi::InterruptHandler* gHandler = nullptr;

void izi::isr::pcint1::attach(izi::InterruptHandler& handler)
{
  handler._next = gHandler;
  gHandler = &handler;
}

ISR(PCINT1_vect, ISR_NOBLOCK)
{
  auto handler = gHandler;
  while(handler) {
    handler->isr();
    handler = handler->_next;
  }
}

#endif