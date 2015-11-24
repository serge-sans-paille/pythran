#ifndef PYTHONIC_INCLUDE_NUMPY_FROMITER_HPP
#define PYTHONIC_INCLUDE_NUMPY_FROMITER_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/numpy/float64.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class Iterable, class dtype = functor::float64>
    types::ndarray<typename std::remove_cv<typename std::remove_reference<
                       Iterable>::type>::type::value_type,
                   1>
    fromiter(Iterable &&iterable, dtype d = dtype(), long count = -1);

    DECLARE_FUNCTOR(pythonic::numpy, fromiter);
  }
}

#endif
