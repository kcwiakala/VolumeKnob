#pragma once

#include <izi/button.hpp>
#include <izi/port.hpp>
#include <izi/encoder.hpp>

#if defined (__AVR_ATtiny45__) || defined (__AVR_ATtiny85__) 

using encoder_t = izi::Encoder< izi::PortB<0>, izi::PortB<1> >;
using button_t = izi::PolledButton< izi::PortB<2> >;
using isr_t = izi::isr::pcint;
using led_t = izi::PortB<3>;

#else

using encoder_t = izi::Encoder< izi::PortB<0>, izi::PortB<1> >;
using button_t = izi::PolledButton< izi::PortB<2> >;
using isr_t = izi::isr::pcint0;
using led_t = izi::PortB<3>;

#endif
