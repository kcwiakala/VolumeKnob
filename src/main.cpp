/* Name: main.c
 * Project: hid-mouse, a very simple HID example
 * Author: Christian Starkjohann
 * Creation Date: 2008-04-07
 * Tabsize: 4
 * Copyright: (c) 2008 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 */

/*
This example should run on most AVRs with only little changes. No special
hardware resources except INT0 are used. You may have to change usbconfig.h for
different I/O pins for USB. Please note that USB D+ must be the INT0 pin, or
at least be connected to INT0 as well.

We use VID/PID 0x046D/0xC00E which is taken from a Logitech mouse. Don't
publish any hardware using these IDs! This is for demonstration only!
*/
// #include <avr/sfr_defs.h>
// #include <avr/iotnx5.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>  /* for sei() */
#include <util/delay.h>     /* for _delay_ms() */

#include <avr/pgmspace.h>   /* required by usbdrv.h */
#include <usbdrv.h>
#include <oddebug.h>        /* This is also an example for using debug macros */

// #include <izi/uart.h>
#include <izi/port.hpp>
#include <izi/debug.hpp>
#include <izi/encoder.hpp>
#include <izi/math.hpp>
#include <izi/lock.hpp>
#include <izi/mpl.hpp>

#define USB_HID_MUTE      0x01
#define USB_HID_VOL_UP    0x02
#define USB_HID_VOL_DEC   0x04

template <class T, size_t N>
constexpr size_t array_length(const T (&array)[N]) noexcept
{
    return N;
}

/* ------------------------------------------------------------------------- */
/* ----------------------------- USB interface ----------------------------- */
/* ------------------------------------------------------------------------- */
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

struct DescriptorChecker 
{
    using actual_length_t = izi::integral_type<array_length(usbHidReportDescriptor)>;
    using expected_length_t = izi::integral_type<USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH>;
    using valid_t = izi::is_same<actual_length_t, expected_length_t>;

    // static constexpr size_t descriptor_length = array_length(usbHidReportDescriptor);
    // static constexpr bool valid = is_same
    // template<size_t> struct actual_length;
    // template<> struct actual_length<USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH> {};
    // static constexpr actual_length<descriptor_length> x = {};
    // static_assert(valid, "Provided USB HID descriptor has invalid length");
    static_assert(valid_t::value, "Provided USB HID descriptor has invalid length");
};

// using dd = decltype(check_descriptor(usbHidReportDescriptor));
// static_assert(check_descriptor(usbHidReportDescriptor), "USB HID descriptor has invalid length");
// nodef<array_length(usbHidReportDescriptor)> a;


static uchar reportBuffer[1];
static uchar idleRate;   /* repeat rate for keyboards, never used for mice */

/* ------------------------------------------------------------------------- */

usbMsgLen_t usbFunctionSetup(uchar data[8])
{
    usbRequest_t* rq = reinterpret_cast<usbRequest_t*>(data);
    /* The following requests are never used. But since they are required by
     * the specification, we implement them in this example.
     */
    if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS){    /* class request type */
        // DBG1(0x50, &rq->bRequest, 1);   /* debug output: print our request */
        if(rq->bRequest == USBRQ_HID_GET_REPORT){  /* wValue: ReportType (highbyte), ReportID (lowbyte) */
            /* we only have one report type, so don't look at wValue */
            usbMsgPtr = (usbMsgPtr_t)&reportBuffer;
            return sizeof reportBuffer;
        }else if(rq->bRequest == USBRQ_HID_GET_IDLE){
            usbMsgPtr = &idleRate;
            return 1;
        }else if(rq->bRequest == USBRQ_HID_SET_IDLE){
            idleRate = rq->wValue.bytes[1];
        }
    }else{
        /* no vendor specific requests implemented */
    }
    return 0;   /* default for not implemented requests: return no data back to host */
}

/* ------------------------------------------------------------------------- */

void sendKeyPress(uint8_t key) {
    while (!usbInterruptIsReady()) {
        wdt_reset();
        usbPoll();       
    }
    reportBuffer[0] = key;
    usbSetInterrupt((uchar*)&reportBuffer, sizeof(reportBuffer));
}

void sendKeyStroke(const uint8_t key, uint8_t times = 1) {
    while(times--) {
        sendKeyPress(key);
        sendKeyPress(0);
    }
}

int main(void)
{
    wdt_enable(WDTO_1S);
    /* If you don't use the watchdog, replace the call above with a wdt_disable().
     * On newer devices, the status of the watchdog (on/off, period) is PRESERVED
     * OVER RESET!
     */
    /* RESET status: all port bits are inputs without pull-up.
     * That's the way we need D+ and D-. Therefore we don't need any
     * additional hardware initialization.
     */
    izi::Encoder<izi::PortB<0>, izi::PortB<1>, izi::isr::pcint0> encoder;
    PCMSK0 = 0x01; 
    PCICR |= _BV(PCIE0);

    odDebugInit();
    DBG1(0x00, 0, 0);       /* debug output: main starts */
    usbInit();
    usbDeviceDisconnect();  /* enforce re-enumeration, do this while interrupts are disabled! */
    wdt_reset();
    _delay_ms(300);
    wdt_reset();
    usbDeviceConnect();
    sei();
    DBG1(0x01, 0, 0);       /* debug output: main loop starts */
    for(;;) {
        wdt_reset();        
        const int8_t delta = encoder.read();
        if(delta != 0) {
            sendKeyStroke((delta < 0) ? USB_HID_VOL_DEC : USB_HID_VOL_UP, izi::min(2, abs(delta)));
        } else {
            usbPoll();
        }
    }
}