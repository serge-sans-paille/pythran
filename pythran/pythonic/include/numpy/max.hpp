#ifndef PYTHONIC_INCLUDE_NUMPY_MAX_HPP
#define PYTHONIC_INCLUDE_NUMPY_MAX_HPP

#include "pythonic/include/numpy/reduce.hpp"
#include "pythonic/include/operator_/imax.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    auto max(E &&e)
        -> decltype(reduce<operator_::functor::imax>(std::forward<E>(e)));

    template <class E, class Opt>
    auto max(E &&e, Opt &&opt)
        -> decltype(reduce<operator_::functor::imax>(std::forward<E>(e),
                                                     std::forward<Opt>(opt)));

    DECLARE_FUNCTOR(pythonic::numpy, max);
  }
}

#endif
