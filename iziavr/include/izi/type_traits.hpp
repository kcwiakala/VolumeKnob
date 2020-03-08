#pragma once

#include <izi/mpl.hpp>

namespace izi {

template<bool B, class T=void> struct enable_if {};
template<class T> struct enable_if<true, T> { typedef T type; };
template< bool B, class T = void > using enable_if_t = typename enable_if<B,T>::type;

template<class T> struct remove_cv                   { typedef T type; };
template<class T> struct remove_cv<const T>          { typedef T type; };
template<class T> struct remove_cv<volatile T>       { typedef T type; };
template<class T> struct remove_cv<const volatile T> { typedef T type; };
 
template<class T> struct remove_const                { typedef T type; };
template<class T> struct remove_const<const T>       { typedef T type; };
 
template<class T> struct remove_volatile             { typedef T type; };
template<class T> struct remove_volatile<volatile T> { typedef T type; };


template<class T> struct is_pointer_helper: false_type {};
template<class T> struct is_pointer_helper<T*>: true_type {};
 
template<class T> struct is_pointer: is_pointer_helper<typename remove_cv<T>::type> {};

template<typename T> struct is_signed: bool_type<(T(-1) < T(0))> {};

template<typename T> struct is_integral: false_type {};
template<> struct is_integral<char>: true_type {};
template<> struct is_integral<short>: true_type {};
template<> struct is_integral<int>: true_type {};
template<> struct is_integral<long>: true_type {};
template<> struct is_integral<long long>: true_type {};
template<> struct is_integral<unsigned char>: true_type {};
template<> struct is_integral<unsigned short>: true_type {};
template<> struct is_integral<unsigned int>: true_type {};
template<> struct is_integral<unsigned long>: true_type {};
template<> struct is_integral<unsigned long long>: true_type {};

template<typename T> struct is_floating_point: false_type {};
template<> struct is_floating_point<float>: true_type {};
template<> struct is_floating_point<double>: true_type {};
template<> struct is_floating_point<long double>: true_type {};

template<class T, class U>
struct is_same: izi::false_type {};
 
template<class T>
struct is_same<T, T>: izi::true_type {};

} // namespace izi