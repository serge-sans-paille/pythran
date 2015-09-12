#ifndef PYTHONIC_INCLUDE_NUMPY_ANGLE_HPP
#define PYTHONIC_INCLUDE_NUMPY_ANGLE_HPP

#include "pythonic/include/numpy/angle_in_deg.hpp"
#include "pythonic/include/numpy/angle_in_rad.hpp"
#include "pythonic/include/types/assignable.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T>
    auto angle(T const &t, bool in_deg) ->
        typename assignable<decltype(proxy::angle_in_rad()(t))>::type;

    // Numpy_expr can be use if only the first argument is given.
    template <class T>
    auto angle(T const &t) -> decltype(proxy::angle_in_rad()(t));

    PROXY_DECL(pythonic::numpy, angle);
  }
}

#endif
