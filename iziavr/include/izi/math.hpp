#pragma once

namespace izi {

template<typename T, typename L>
T max(const T a, const L b) {
  return (a>b) ? a : b;
}

template<typename T, typename U>
T min(const T a, const U b) {
  return (a>b) ? b : a;
}

template<typename T, typename L, typename U>
T clamp(const T a, const L lb, const U ub) {
  return max(min(a, ub), lb);
}

} // namespace izi
