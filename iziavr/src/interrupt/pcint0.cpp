#include <avr/interrupt.h>
#include <izi/interrupt.hpp>

using hander = izi::InterruptHandler<izi::isr::pcint0>;

template<> hander* hander::_instance = nullptr;

ISR(PCINT0_vect)
{
    hander::execute();
}