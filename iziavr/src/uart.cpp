#include <avr/interrupt.h>

#include <izi/uart.hpp>

static izi::detail::UartIsrHandler* gHandler = nullptr;

izi::detail::UartIsrHandler::UartIsrHandler()
{
  gHandler = this;
}

ISR(USART_UDRE_vect)
{
  gHandler->txIsr();
}

ISR(USART_RX_vect)
{
  gHandler->rxIsr();
}