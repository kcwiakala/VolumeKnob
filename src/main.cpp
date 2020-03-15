#include <avr/wdt.h>

#include <izi/button.hpp>
#include <izi/delay.hpp>
#include <izi/math.hpp>
#include <izi/port.hpp>
// #include <izi/debug.hpp>
#include <izi/encoder.hpp>

#include "VolumeController.hpp"

using encoder_t = izi::Encoder< izi::PortB<0>, izi::PortB<1> >;
using button_t = izi::PolledButton< izi::PortB<2> >;

VolumeController controller;
encoder_t encoder;
button_t button;

int main(void)
{
  wdt_enable(WDTO_1S);
  

  izi::isr::pcint0::setup<encoder_t::clk_t>();
  izi::isr::pcint0::attach(encoder);
  izi::isr::pcint0::enable(true);

  izi::PortB<3>::setup(true, false);

  controller.init();

  for(;;) {
    wdt_reset();
    izi::delay(20_ms);
    controller.update(izi::clamp(encoder.delta(), -5, 5));  
    if(button.clicked()) {
      controller.mute();
    }
  }
}