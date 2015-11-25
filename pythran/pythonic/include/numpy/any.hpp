#ifndef PYTHONIC_INCLUDE_NUMPY_ANY_HPP
#define PYTHONIC_INCLUDE_NUMPY_ANY_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/__builtin__/ValueError.hpp"
#include "pythonic/include/numpy/add.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    typename std::enable_if<types::is_numexpr_arg<E>::value, bool>::type
    any(E const &expr, types::none_type _ = types::none_type());

    template <class E>
    typename std::enable_if<
        std::is_scalar<E>::value or types::is_complex<E>::value, bool>::type
    any(E const &expr, types::none_type _ = types::none_type());

    template <class E>
    auto any(E const &array, long axis) ->
        typename std::enable_if<std::is_scalar<E>::value or
                                    types::is_complex<E>::value,
                                decltype(any(array))>::type;

    template <class E>
    auto any(E const &array, long axis) ->
        typename std::enable_if<E::value == 1, decltype(any(array))>::type;

    template <class E>
    typename std::enable_if<
        E::value != 1, types::ndarray<typename E::dtype, E::value - 1>>::type
    any(E const &array, long axis);

    DECLARE_FUNCTOR(pythonic::numpy, any);
  }
}

#endif
