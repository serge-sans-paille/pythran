#ifndef PYTHONIC_INCLUDE_NUMPY_MIN_HPP
#define PYTHONIC_INCLUDE_NUMPY_MIN_HPP

#include "pythonic/include/numpy/reduce.hpp"
#include "pythonic/include/operator_/imin.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class E>
    auto min(E &&e)
        -> decltype(reduce<operator_::functor::imin>(std::forward<E>(e)));

    template <class E, class Opt>
    auto min(E &&e, Opt &&opt)
        -> decltype(reduce<operator_::functor::imin>(std::forward<E>(e),
                                                     std::forward<Opt>(opt)));

    DECLARE_FUNCTOR(pythonic::numpy, min);
  }
}

#endif
