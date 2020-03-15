#pragma once

#include <izi/bitmask.hpp>

namespace izi {
namespace utils {

struct Flags 
{
  template<uint8_t f>
  void set_flag(const bool value) { 
    bitmask<f>::set(_flags, value);
  }

  template<uint8_t f>
  bool get_flag() const {
    bitmask<f>::get(_flags);
  }

private:
  uint8_t _flags;
};

} // namepsace utils
} // namsepace izi