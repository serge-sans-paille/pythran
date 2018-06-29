#ifndef PYTHONIC_INCLUDE_NUMPY_APPEND_HPP
#define PYTHONIC_INCLUDE_NUMPY_APPEND_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class T, class pS, class F>
  types::ndarray<
      typename std::remove_cv<typename std::remove_reference<
          decltype(std::declval<T>() +
                   std::declval<typename utils::nested_container_value_type<
                       F>::type>())>::type>::type,
      types::pshape<long>>
  append(types::ndarray<T, pS> const &nto, F const &data);

  template <class T, class F>
  types::ndarray<
      typename std::remove_cv<typename std::remove_reference<
          decltype(std::declval<typename utils::nested_container_value_type<
                       types::list<T>>::type>() +
                   std::declval<typename utils::nested_container_value_type<
                       F>::type>())>::type>::type,
      types::pshape<long>>
  append(types::list<T> const &to, F const &data);

  DECLARE_FUNCTOR(pythonic::numpy, append);
}
PYTHONIC_NS_END

#endif
