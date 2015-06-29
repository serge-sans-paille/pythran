#ifndef PYTHONIC_INCLUDE_NUMPY_VAR_HPP
#define PYTHONIC_INCLUDE_NUMPY_VAR_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/builtins/None.hpp"
#include "pythonic/builtins/ValueError.hpp"
#include "pythonic/numpy/add.hpp"
#include "pythonic/numpy/mean.hpp"
#include "pythonic/numpy/reshape.hpp"
#include "pythonic/numpy/sum.hpp"

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
    auto var(E const &expr, types::none_type axis = builtins::None,
             types::none_type dtype = builtins::None,
             types::none_type out = builtins::None, long ddof = 0)
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
    auto var(E const &expr, long axis, types::none_type dtype = builtins::None,
             types::none_type out = builtins::None, long ddof = 0) ->
        typename assignable<decltype(var_type<E>() * mean(expr, axis))>::type;

    PROXY_DECL(pythonic::numpy, var);
  }
}

#endif
