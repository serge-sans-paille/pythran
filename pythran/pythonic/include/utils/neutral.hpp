#ifndef PYTHONIC_INCLUDE_UTILS_NEUTRAL_HPP
#define PYTHONIC_INCLUDE_UTILS_NEUTRAL_HPP

#include "pythonic/include/operator_/iadd.hpp"
#include "pythonic/include/operator_/imul.hpp"
#include "pythonic/include/operator_/imax.hpp"
#include "pythonic/include/operator_/imin.hpp"

PYTHONIC_NS_BEGIN

namespace utils
{
  template <class Op, class T>
  struct neutral;

  template <class T>
  struct neutral<operator_::functor::iadd, T> {
    static T const value;
  };
  template <class T>
  T const neutral<operator_::functor::iadd, T>::value = 0;

  template <class T>
  struct neutral<operator_::functor::imul, T> {
    static T const value;
  };
  template <class T>
  T const neutral<operator_::functor::imul, T>::value = 1;

  template <class T>
  struct neutral<operator_::functor::imax, T> {
    static T const value;
  };

  template <class T>
  T const neutral<operator_::functor::imax, T>::value =
      std::numeric_limits<T>::lowest();

  template <class T>
  struct neutral<operator_::functor::imin, T> {
    static T const value;
  };

  template <class T>
  T const neutral<operator_::functor::imin, T>::value =
      std::numeric_limits<T>::max();
}
PYTHONIC_NS_END

#endif
