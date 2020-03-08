#pragma once

#include <stdint.h>

#include <avr/io.h>

#if defined UDRE
  #define IZI_UDRE UDRE
#else
	#define IZI_UDRE UDRE0
#endif

#if defined UCR
	#define IZI_UCR UCR
#elif defined UCSRB
  #define IZI_UCR UCSRB
#elif defined UCSR0B
  #define IZI_UCR UCSR0B
#endif

#if defined UDR
  #define IZI_UDR UDR
#elif defined UDR0
  #define IZI_UDR UDR0
#endif

#if defined USR
  #define IZI_USR USR
#elif defined UCSRA
  #define IZI_USR UCSRA
#elif defined UCSR0A
  #define IZI_USR UCSR0A
#endif

#if defined UBRR
  #define IZI_UBRRL UBRR
#elif defined UBRRL
  #define IZI_UBRRL UBRRL
#elif defined UBRR0
  #define IZI_UBRRL UBRR0
#elif defined UBRR0L
  #define IZI_UBRRL UBRR0L
#endif

#if defined UBRRH
  #define IZI_UBRRH UBRRH
#elif defined UBRR1
  #define IZI_UBRRH UBRR1
#elif defined UBRR0H
  #define IZI_UBRRH UBRR0H
#endif

#if defined TXEN
  #define IZI_TXEN TXEN
#else
  #define IZI_TXEN TXEN0
#endif

namespace izi {

template<uint32_t baudrate>
class Uart
{
	static constexpr uint32_t br = F_CPU/(16*baudrate)-1;
	static constexpr uint8_t brl = br & 0xFF;
	static constexpr uint8_t brh = (br >> 8) & 0xFF;

public:
	Uart() {
		IZI_UCR |= (1<<IZI_TXEN);
		IZI_UBRRL = brl;
		#if defined IZI_UBRRH
		IZI_UBRRH = brh;
		#endif
	}

protected:
	void tx(char c) const {
		while(!(IZI_USR & (1 << IZI_UDRE)));
		IZI_UDR = c;
	}
};

} // namespace izi