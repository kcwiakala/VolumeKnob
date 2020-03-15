#pragma once

#include <stdlib.h>

namespace izi {

template<typename T>
class vector {
public:
  void push_back(const T& v) {
    _data = (T*)realloc((void*)_data, sizeof(T)*(_size + 1));
    *(_data+_size) = v;
    ++_size;
  }

  T* begin() {
    return _data;
  }

  T* end() {
    return _data + _size;
  }

  uint8_t size() const {
    return _size;
  }

private:
  uint8_t _size = 0;
  T* _data = nullptr;
};

} // namespace izi
