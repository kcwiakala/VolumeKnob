#include <avr/interrupt.h>
#include <izi/interrupt.hpp>

#ifdef PCMSK

izi::InterruptHandler* gHandler = nullptr;

void izi::isr::pcint::attach(izi::InterruptHandler& handler)
{
  handler._next = gHandler;
  gHandler = &handler;
}

ISR(PCINT_vect, ISR_NOBLOCK)
{
  auto handler = gHandler;
  while(handler) {
    handler->isr();
    handler = handler->_next;
  }
}

#endif