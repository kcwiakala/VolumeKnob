#include <stdlib.h>

#include <izi/bitmask.hpp>
#include <izi/mpl.hpp>
#include <izi/type_traits.hpp>

#include "VolumeController.hpp"

PROGMEM const char usbHidReportDescriptor[] = {
    0x05, 0x0C,        // Usage Page (Consumer)
    0x09, 0x01,        // Usage (Consumer Control)
    0xA1, 0x01,        // Collection (Application)
    0x05, 0x0C,        //   Usage Page (Consumer)
    0x15, 0x00,        //   Logical Minimum (0)
    0x25, 0x01,        //   Logical Maximum (1)
    0x75, 0x01,        //   Report Size (1)
    0x95, 0x07,        //   Report Count (3)
    0x09, 0xE2,        //   Usage (Mute)
    0x09, 0xE9,        //   Usage (Volume Increment)
    0x09, 0xEA,        //   Usage (Volume Decrement)
    0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,              // End Collection
};

using MUTE_KEY = izi::bitmask<0>;
using VINC_KEY = izi::bitmask<1>;
using VDEC_KEY = izi::bitmask<2>;

VolumeController::VolumeController(): HidDevice(usbHidReportDescriptor)
{
}

void VolumeController::init()
{
  HidDevice::init();
  stroke(0,2);
}

void VolumeController::update(int8_t delta)
{
    if(delta < 0) {
        stroke(VDEC_KEY::mask, abs(delta));
    } else if (delta > 0) {
        stroke(VINC_KEY::mask, abs(delta));
    }
}

void VolumeController::mute()
{
    stroke(MUTE_KEY::mask);
}

void VolumeController::press(const uint8_t key) 
{
    waitForHost();
    _reportBuffer = key;
    setInterrupt();
}

void VolumeController::stroke(const uint8_t key, uint8_t times) 
{
    while(times--) {
        press(key);
        press(0);
    }
}