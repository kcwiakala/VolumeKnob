#pragma once

namespace izi {

template<typename T, uint8_t Size>
struct buffer
{
  void push(T v) {
    _data[(_head + _count) % Size] = v;
    ++_count;
  }

  T get() {
    const T v = _data[_head];
    _head = (_head + 1) % Size;
    --_count;
    return v;
  }

  bool full() const {
    return _count >= Size;
  }

  bool empty() const {
    return _count == 0;
  }

  void clear() {
    _count = 0;
  }

private:
  T _data[Size];
  uint8_t _head = 0;
  uint8_t _count = 0;
};

} // namespace izi