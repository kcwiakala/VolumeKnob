#pragma once

#include <vusb/usbdrv.h>

namespace vusb {
namespace detail {

class HidDeviceBase
{
public:
  ~HidDeviceBase() {}

  void init();

  virtual usbMsgLen_t functionSetup(usbRequest_t& request);
};

} // namespace detail
} // namespace vusb
