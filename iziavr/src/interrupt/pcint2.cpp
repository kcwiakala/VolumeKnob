#include <avr/interrupt.h>
#include <izi/interrupt.hpp>

izi::InterruptHandler* gHandler = nullptr;

void izi::isr::pcint2::attach(izi::InterruptHandler& handler)
{
  handler._next = gHandler;
  gHandler = &handler;
}

ISR(PCINT2_vect, ISR_NOBLOCK)
{
  auto handler = gHandler;
  while(handler) {
    handler->isr();
    handler = handler->_next;
  }
}