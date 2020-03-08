#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

namespace izi {
namespace utils {

template<int ... bits> struct BitMask;

template<int b>
struct BitMask<b>
{
    static_assert(b<8, "Only 8-bit masks are supported");
    static constexpr uint8_t mask = (1 << b);
};

template<int b, int ... bits>
struct BitMask<b, bits...>
{
    static constexpr uint8_t mask = (1 << b) | BitMask<bits...>::mask;
};

template<int b1>
uint8_t collapse(uint8_t value)
{
    return (value >> b1) & 0x01;
}

template<int b1, int b2, int ... bits>
uint8_t collapse(uint8_t value)
{
    return collapse<b1>(value) | (collapse<b2, bits...>(value) << (1+sizeof...(bits)));
}

} // namespace utils

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

namespace details {

template<typename Traits, int ... bits>
struct Port
{
    static constexpr uint8_t mask = utils::BitMask<bits...>::mask;
    static constexpr uint8_t size = sizeof...(bits);
    
    Port(const bool output = true, const bool pullup = false) 
    {
        setup(output);
        set(pullup);
    }

    void setup(const bool output) const
    {
        if(output) {
            Traits::output(mask);
        } else {
            Traits::input(mask);
        }
    }

    void set(const bool value) const
    {
        if(value) {
            Traits::set(mask);
        } else {
            Traits::clear(mask);
        }
    }

    void toggle() const 
    {
        Traits::toggle(mask);
    }

    uint8_t get() const
    {
        return Traits::get(mask);
    }

    bool any() const
    {
        return get() != 0;
    }

    bool all() const
    {
        return get() == mask;
    }

    uint8_t collapsed() const
    {
        return utils::collapse<bits...>(get());
    }
};

} // namespace details

template<int ... bits> 
using PortA = details::Port<traits::A, bits...>;

template<int ... bits> 
using PortB = details::Port<traits::B, bits...>;

template<int ... bits> 
using PortC = details::Port<traits::C, bits...>;

template<int ... bits> 
using PortD = details::Port<traits::D, bits...>;

template<class Input>
class Encoder
{
    static_assert(Input::size == 2, "Invalid encoder input size");
public:
    Encoder(const bool pullup = true): input(false, true) {}

    int8_t update() 
    {
        static constexpr uint8_t lookup[] = {0, 1, 3, 2};
        const uint8_t value = lookup[input.collapsed()];
        if(prev_value == 0xFF) {
            prev_value = value;
            prev_delta = 0;
        } else {
            int8_t delta = value - prev_value;
            if(delta == -3) { // 3 -> 0
                prev_delta = 1;
            } else if (delta == 3) { // 0 -> 3  
                prev_delta = -1;
            } else if (abs(delta) < 2) {
                prev_delta = delta;
            }
            prev_value = value;
        }
        return prev_delta;
    }

private:
    uint8_t prev_value = 0xFF;
    int8_t prev_delta = 0;
    Input input;
};


struct endl_t {};

// namespace traits {

// template<unsigned size> struct Integral;
// template<> Integral<1> { static constexpr unsigned print_size=3; };
// template<> Integral<2> { static constexpr unsigned print_size=5; };
// template<> Integral<4> { static constexpr unsigned print_size=10; };

// template<typename T>
// struct Print;

// template<> 
// struct Print<int> 
// { 
//     static constexpr int buffer_size = 11; 
// };

// }



} // namespace izi