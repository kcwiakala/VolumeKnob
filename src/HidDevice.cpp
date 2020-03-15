#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include <izi/delay.hpp>

#include "HidDevice.hpp"

static IHidDevice* gDevice = nullptr;

void IHidDevice::init()
{
  gDevice = this;
  cli();
  usbInit();
  usbDeviceDisconnect();  /* enforce re-enumeration, do this while interrupts are disabled! */
  wdt_reset();
  izi::delay(300_ms);
  wdt_reset();
  usbDeviceConnect();
  sei();
}

usbMsgLen_t IHidDevice::functionSetup(usbRequest_t& request)
{
  return 0;
}

usbMsgLen_t usbFunctionSetup(uchar data[8])
{
  gDevice->functionSetup(reinterpret_cast<usbRequest_t&>(*data));
}