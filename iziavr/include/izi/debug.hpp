#pragma once

#include <stdint.h>
#include <stdio.h>

#include <izi/utils/math.hpp>
#include <izi/uart.hpp>
#include <izi/utils/flags.hpp>

namespace izi {

const char* const endl = "\r\n";

template< uint32_t baudrate, uint8_t precision = 2 >
class Debug: public Uart<baudrate, 8, 0>, public utils::Flags
{
  static_assert(precision < 7, "Too large precision specified");
  static constexpr unsigned long p_mul = utils::pow<10,precision>::value;

public:
  Debug& operator<<(const char c) {
    this->tx(c);
    return *this;
  }

  Debug& operator<<(const char* c) {
    while(*c != 0) {
      this->tx(*c++);
    }
    return *this;
  }

  Debug& operator<<(bool b) {
    this->tx(b ? '1' : '0');
    return *this;
  }

  template<typename T>
  Debug& operator<<(T v) {
    format(v);
    return *this;
  }

private:
  template<typename T>
  void format(T v, const uint8_t w, const bool padding = false) const
  {
    char buffer[w];
    uint8_t size = 0;
    if(v<0) {
      this->tx('-');
      v = -v;
    } else if (v == 0) {
      buffer[size++] = '0';
    }
    for(;v!=0;v/=10) {
      buffer[size++] = '0' + v%10;
    }
    if(padding) {
      while(size<w) {
        buffer[size++] = '0';
      }
    }
    while(size) {
      this->tx(buffer[--size]);
    }
  }

  template<typename T, enable_if_t<is_integral<T>::value, int> = 0>
  void format(const T v) const {
    if(get_flag<0>()) {
      this->tx('0');
      this->tx('x');
      for(int8_t i=0; i<utils::digits<T>::hex; ++i) {
        const uint8_t h = 0x0F & (v >> 4*(utils::digits<T>::hex-1-i));
        this->tx(h + (h < 10 ? '0' : 'A'-10));
      }    
    } else {
      format(v, utils::digits<T>::dec);
    }
  }

  template<typename T, enable_if_t<is_floating_point<T>::value, int> = 0>
  void format(const T v) {
    format(static_cast<long>(v));
    this->tx('.');
    format(static_cast<unsigned long>(v*p_mul)%p_mul, precision, true);
  }
};

} // namespace izi