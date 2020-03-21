#pragma once

#include <izi/bitmask.hpp>
#include <izi/preprocessor.hpp>

#ifdef UDR0
  #define IZI_UART_DEVICE 0
  #ifdef UBRR0L
    #define IZI_UART_BRH
  #endif
#else
  #define IZI_UART_DEVICE
  #ifdef UBRRL
    #define IZI_UART_BRH
  #endif

#endif

#define IZI_UART_REG(name)       IZI_CAT(name,IZI_UART_DEVICE)
#define IZI_UART_REGX(name,sfx)  IZI_CAT(name,IZI_CAT(IZI_UART_DEVICE,sfx))
#define IZI_UART_FLAG(name)      IZI_CAT(name,IZI_UART_DEVICE)

#ifdef USR
  #define IZI_USR USR
#else
  #define IZI_USR IZI_UART_REGX(UCSR,A)
#endif

#ifdef UCR
  #define IZI_UCR UCR
#else
  #define IZI_UCR IZI_UART_REGX(UCSR,B)
#endif

namespace izi {
namespace traits {

struct Uart {

  static auto data()  -> decltype(IZI_UART_REG(UDR)) { return IZI_UART_REG(UDR); }
  
  template<uint32_t baudrate>
  static void setup()
  {
    constexpr uint32_t bdr = F_CPU/(16*baudrate)-1;
    #if defined IZI_UART_BRH      
      IZI_UART_REGX(UBRR,L) = bdr & 0xFF;
      IZI_UART_REGX(UBRR,H) = (bdr >> 8) & 0xFF;
    #else
      IZI_UART_REG(UBRR) = bdr & 0xFF;
    #endif
  }

  static auto status() -> decltype(IZI_USR) { return IZI_USR; }

  static auto ctrl() -> decltype(IZI_UCR) { return IZI_UCR; }

  static void enableRxIsr(const bool enabled) { 
    izi::bitmask<IZI_UART_FLAG(RXCIE)>::set(ctrl(), enabled);
  }

  static void enableTxIsr(const bool enabled) { 
    izi::bitmask<IZI_UART_FLAG(UDRIE)>::set(ctrl(), enabled);
  }
};

} // namespace traits
} // namespace izi 