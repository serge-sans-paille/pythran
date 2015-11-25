#ifndef PYTHONIC_INCLUDE_NUMPY_VAR_HPP
#define PYTHONIC_INCLUDE_NUMPY_VAR_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/__builtin__/None.hpp"
#include "pythonic/include/__builtin__/ValueError.hpp"
#include "pythonic/include/numpy/add.hpp"
#include "pythonic/include/numpy/mean.hpp"
#include "pythonic/include/numpy/reshape.hpp"
#include "pythonic/include/numpy/sum.hpp"

#include <algorithm>

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    using var_type =
        typename std::conditional<std::is_integral<typename E::dtype>::value,
                                  double, typename E::dtype>::type;

    template <class E>
    auto var(E const &expr, types::none_type axis = __builtin__::None,
             types::none_type dtype = __builtin__::None,
             types::none_type out = __builtin__::None, long ddof = 0)
        -> decltype(var_type<E>(mean(expr)));

    // this is a workaround for the lack of efficient support for broadcasting
    // in pythonic
    template <class T, class E, class M>
    void _enlarge_copy_minus(T &&t, E const &e, M const &m, long axis,
                             utils::int_<1>);

    template <class T, class E, class M, size_t N>
    void _enlarge_copy_minus(T &&t, E const &e, M const &m, long axis,
                             utils::int_<N>);

    template <class E>
    auto var(E const &expr, long axis,
             types::none_type dtype = __builtin__::None,
             types::none_type out = __builtin__::None, long ddof = 0) ->
        typename assignable<decltype(var_type<E>() * mean(expr, axis))>::type;

    DECLARE_FUNCTOR(pythonic::numpy, var);
  }
}

#endif
