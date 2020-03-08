#pragma once

namespace izi {

template<typename T, size_t N>
class vector {
public:
    void push_back(const T& v) {
        _data[_size++] = v;
    }

    T operator[](const uint8_t i) {
        return _data[i];
    }

private:
    uint8_t _size;
    T _data[N];
};

} // namespace izi
