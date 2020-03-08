#pragma once

namespace izi {

template<bool B, typename TrueType, typename FalseType>
struct if_c: FalseType { };

template<typename TrueType, typename FalseType>
struct if_c<true, TrueType, FalseType>: TrueType { };

template<typename T, typename TrueType, typename FalseType>
struct if_: if_c<T::value, TrueType, FalseType> { };

template<int V>
struct integral_type { static constexpr int value = V; };

template<bool V> 
struct bool_type: integral_type<int(V)> { };

struct true_type: bool_type<true> { };
struct false_type: bool_type<false> { };

template<int T> struct none_type;

} // namespace izi