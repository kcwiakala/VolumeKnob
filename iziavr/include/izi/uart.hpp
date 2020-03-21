#pragma once

#include <stdint.h>

#include <avr/io.h>

#include <izi/bitmask.hpp>
#include <izi/buffer.hpp>
#include <izi/delay.hpp>
#include <izi/lock.hpp>
#include <izi/traits/uart.hpp>

namespace izi {
namespace detail {
  
struct UartIsrHandler
{
  UartIsrHandler();
  virtual void rxIsr() { }
  virtual void txIsr() { }
};

template<uint8_t TxBufferSize>
class UartTransmitter: UartIsrHandler
{
public:
	void tx(char c) {
    izi::Lock lock;
    lock.wait([this] () { return _txBuffer.full(); });
    _txBuffer.push(c);
    traits::Uart::enableTxIsr(true);
	}

private:
  void txIsr() override {
    if(_txBuffer.empty()) {
      traits::Uart::enableTxIsr(false);
    } else {
      traits::Uart::data() = _txBuffer.get();
    }
  }

  buffer<char, TxBufferSize> _txBuffer;
};

template<uint8_t TxBufferSize, uint8_t RxBufferSize>
class Uart: public UartTransmitter<TxBufferSize>
{
public:
  Uart() {
    izi::bitmask<IZI_UART_FLAG(TXEN), IZI_UART_FLAG(RXEN)>::set(traits::Uart::ctrl());
    traits::Uart::enableRxIsr(true);
  }

  char rx() {
    izi::Lock lock;
    lock.wait([this] () { return _rxBuffer.full(); });
    return _rxBuffer.get();
  }

private:
  void rxIsr() override {
    if(!_rxBuffer.full()) {
      _rxBuffer.push(traits::Uart::data());
    }
  }

private:
  buffer<char, RxBufferSize> _rxBuffer;
};

template<uint8_t TxBufferSize>
class Uart<TxBufferSize, 0>: public UartTransmitter<TxBufferSize> 
{ 
public:
  Uart() {
    izi::bitmask<IZI_UART_FLAG(TXEN)>::set(traits::Uart::ctrl());
  }
};

} // namespace detail 

template<uint32_t baudrate, uint8_t TxBufferSize = 16, uint8_t RxBufferSize = 16>
class Uart: public detail::Uart<TxBufferSize, RxBufferSize>
{
public:
	Uart() {
    traits::Uart::setup<baudrate>();        
	}
};

} // namespace izi