#pragma once

#include <avr/io.h>

namespace izi {
namespace traits {

#ifdef PORTA
struct PortA 
{
  static auto ddr()  -> decltype(DDRA)   { return DDRA; }
  static auto port() -> decltype(PORTA)  { return PORTA; }
  static auto pin()  -> decltype(PINA)   { return PINA; }
};
#else
struct PortA;
#endif

#ifdef PORTB
struct PortB
{
  static auto ddr()  -> decltype(DDRB)   { return DDRB; }
  static auto port() -> decltype(PORTB)  { return PORTB; }
  static auto pin()  -> decltype(PINB)   { return PINB; }
};
#else
struct PortB;
#endif

#ifdef PORTC
struct PortC
{
  static auto ddr()  -> decltype(DDRC)   { return DDRC; }
  static auto port() -> decltype(PORTC)  { return PORTC; }
  static auto pin()  -> decltype(PINC)   { return PINC; }
};
#else
struct PortC;
#endif

#ifdef PORTD
struct PortD
{
  static auto ddr()  -> decltype(DDRD)  { return DDRD; }
  static auto port() -> decltype(PORTD) { return PORTD; }
  static auto pin()  -> decltype(PIND)  { return PIND; }
};
#else
struct PortD;
#endif

} // namespace traits
} // namespace izi