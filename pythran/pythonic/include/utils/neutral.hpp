#ifndef PYTHONIC_INCLUDE_UTILS_NEUTRAL_HPP
#define PYTHONIC_INCLUDE_UTILS_NEUTRAL_HPP

#include "pythonic/include/operator_/iadd.hpp"
#include "pythonic/include/operator_/imul.hpp"
#include "pythonic/include/operator_/imax.hpp"
#include "pythonic/include/operator_/imin.hpp"

namespace pythonic
{

  namespace utils
  {
    template <class Op, class T>
    struct neutral;

    template <class T>
    struct neutral<operator_::functor::iadd, T> {
      static const T value;
    };

    // FIXME clang doesn't accept it as a static constexpr value for neutral
    template <class T>
    T const neutral<operator_::functor::iadd, T>::value = 0;

    template <class T>
    struct neutral<operator_::functor::imul, T> {
      static constexpr T value = 1;
    };

    template <class T>
    struct neutral<operator_::functor::imax, T> {
      static constexpr T value = std::numeric_limits<T>::lowest();
    };

    template <class T>
    struct neutral<operator_::functor::imin, T> {
      static constexpr T value = std::numeric_limits<T>::max();
    };
  }
}

#endif
