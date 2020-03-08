#pragma once

namespace izi {

template<typename T>
T max(const T a, const T b) {
    return (a>b) ? a : b;
}

template<typename T>
T min(const T a, const T b) {
    return (a>b) ? b : a;
}

} // namespace izi
