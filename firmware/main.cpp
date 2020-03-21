#include <avr/wdt.h>

#include <izi/delay.hpp>
#include <izi/math.hpp>

#include "board.hpp"
#include "VolumeController.hpp"

VolumeController controller;
encoder_t encoder;
button_t button;

int main(void)
{
  wdt_enable(WDTO_1S);
  
  isr_t::setup<encoder_t::clk_t>();
  isr_t::attach(encoder);
  isr_t::enable(true);

  controller.init();

  led_t::setup(true, false);

  for(;;) {
    wdt_reset();
    izi::delay(20_ms);
    controller.update(izi::clamp(encoder.delta(), -5, 5));  
    if(button.clicked()) {
      controller.mute();
    }
  }
}