#ifndef PYTHONIC_TYPES_NUMPY_OP_HELPER_HPP
#define PYTHONIC_TYPES_NUMPY_OP_HELPER_HPP

#include "pythonic/types/numpy_broadcast.hpp"

namespace pythonic {

namespace types {


template<class T0, class... Types>
struct all_valid_arg {
  static constexpr bool value = all_valid_arg<T0>::value and all_valid_arg<Types...>::value;
};
template<class T>
struct all_valid_arg<T> {
  static constexpr bool value = (is_numexpr_arg<T>::value or is_complex<T>::value or std::is_scalar<T>::value);
};

template<class T0, class... Types>
struct any_numexpr_arg {
  static constexpr bool value = is_numexpr_arg<T0>::value or any_numexpr_arg<Types...>::value;
};
template<class T>
struct any_numexpr_arg<T> {
  static constexpr bool value = is_numexpr_arg<T>::value;
};

template<class... Types>
struct valid_numexpr_parameters {
  static constexpr bool value = any_numexpr_arg<Types...>::value and all_valid_arg<Types...>::value;
};


template<class T0, class T1,
         bool numexprarg = valid_numexpr_parameters<T0, T1>::value,
         bool T0_scalar = std::is_scalar<T0>::value or is_complex<T0>::value,
         bool T1_scalar = std::is_scalar<T1>::value or is_complex<T1>::value>
struct the_common_type {
  using type = typename std::conditional < T0::value<T1::value, T1, T0>::type;
};
template<class T0, class T1>
struct the_common_type<T0, T1, true, false, true> {
  using type = T0;
};
template<class T0, class T1>
struct the_common_type<T0, T1, true, true, false> {
  using type = T1;
};
template<class T0, class T1>
struct the_common_type<T0, T1, true, true, true> {
  using type = broadcast<int,int>; // should never happen
};
template<class T0, class T1, bool b0, bool b1>
struct the_common_type<T0, T1, false, b0, b1> {
  using type = broadcast<int,int>; // should never happen
};

template<class... Types> struct common_type;

template<class T0>
struct common_type<T0> {
  using type = T0;
};


template<class T0, class T1>
struct common_type<T0, T1> {
  using type =  typename the_common_type<T0, T1>::type;
};

template<class T0, class T1, class... Types>
struct common_type<T0, T1, Types...> {
  using type = typename common_type<
                  typename common_type<T0, T1>::type,
                  typename common_type<Types...>::type
               >::type;
};

template <class T, class... OtherTypes>
struct adapt_type {
  using ctype = typename common_type<T, OtherTypes...>::type;
  using type = typename std::conditional<std::is_same<T, ctype>::value,
                 T,
                 typename std::conditional<std::is_scalar<T>::value or is_complex<T>::value,
                   broadcast<typename ctype::dtype, T>,
                   broadcasted<T>>::type>::type;
};

}

}

#endif
