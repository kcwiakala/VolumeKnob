#pragma once

namespace izi {

template<typaname T, uint8_t Size>
struct buffer
{
  void push(T v) {
    _back = (_back+1) % Size;
    _data[pos] = v;
  }

  T get() {
    const uint8_t pos = _front;
    _front = (_front+1) % Size;
    return _data[pos];
  }

  uint8_t size() const {
    return (Size + _front - _back) % Size;
  }

private:
  T _data[Size];
  uint8_t _front = 0;
  uint8_t _back = 0;
}

} // namespace izi