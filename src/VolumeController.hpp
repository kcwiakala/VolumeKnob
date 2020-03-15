#pragma once

#include "HidDevice.hpp"

class VolumeController: public HidDevice<uint8_t>
{
public:
  VolumeController();

  void init();

  void update(int8_t delta);

  void mute();

private:
  void stroke(const uint8_t key, uint8_t times = 1);

  void press(const uint8_t key);
};
