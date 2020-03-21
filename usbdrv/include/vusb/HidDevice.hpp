#pragma once

#include <avr/wdt.h>

#include <vusb/detail/HidDeviceBase.hpp>
#include <vusb/detail/ConfigValidator.hpp>

namespace vusb {

template<typename ReportBuffer>
class HidDevice: public detail::HidDeviceBase, detail::ConfigValidator
{
public:
  template <class T>
  HidDevice(const T& hidReportDesctiptor)
  {
    validateReportDescriptor(hidReportDesctiptor);
  }

  void setInterrupt()
  {
    usbSetInterrupt((uchar*)&_reportBuffer, sizeof(_reportBuffer));
  }

  void waitForHost()
  {
    while (!usbInterruptIsReady()) {
      usbPoll();
      wdt_reset();
    }
  }

protected:
    ReportBuffer _reportBuffer;
};

} // namespace vusb