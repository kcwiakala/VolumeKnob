#pragma once

#include <avr/io.h>

namespace izi {
namespace traits {

#ifdef PORTA
struct A 
{
    static void input(const uint8_t mask) { DDRA |= mask; }
    static void output(const uint8_t mask) { DDRA &= ~mask; }
    static void set(const uint8_t mask) { PORTA |= mask; }
    static void clear(const uint8_t mask) { PORTA &= ~mask; }
    static void toggle(const uint8_t mask) { PORTA ^= mask; }
    static uint8_t get(const uint8_t mask) { return PINA & mask; }
};
#else
struct A;
#endif

#ifdef PORTB
struct B
{
    static void input(const uint8_t mask) { DDRB |= mask; }
    static void output(const uint8_t mask) { DDRB &= ~mask; }
    static void set(const uint8_t mask) { PORTB |= mask; }
    static void clear(const uint8_t mask) { PORTB &= ~mask; }
    static void toggle(const uint8_t mask) { PORTB ^= mask; }
    static uint8_t get(const uint8_t mask) { return PINB & mask; }
};
#else
struct B;
#endif

#ifdef PORTC
struct C
{
    static void input(const uint8_t mask) { DDRC |= mask; }
    static void output(const uint8_t mask) { DDRC &= ~mask; }
    static void set(const uint8_t mask) { PORTC |= mask; }
    static void clear(const uint8_t mask) { PORTC &= ~mask; }
    static void toggle(const uint8_t mask) { PORTC ^= mask; }
    static uint8_t get(const uint8_t mask) { return PINC & mask; }
};
#else
struct C;
#endif

#ifdef PORTD
struct D
{
    static void input(const uint8_t mask) { DDRD |= mask; }
    static void output(const uint8_t mask) { DDRD &= ~mask; }
    static void set(const uint8_t mask) { PORTD |= mask; }
    static void clear(const uint8_t mask) { PORTD &= ~mask; }
    static void toggle(const uint8_t mask) { PORTD ^= mask; }
    static uint8_t get(const uint8_t mask) { return PIND & mask; }
};
#else
struct D;
#endif

} // namespace traits
} // namespace izi