#ifndef PYTHONIC_NUMPY_MAX_HPP
#define PYTHONIC_NUMPY_MAX_HPP

#include "pythonic/include/numpy/max.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/numpy/reduce.hpp"
#include "pythonic/operator_/imax.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    auto max(E &&e)
        -> decltype(reduce<operator_::functor::imax>(std::forward<E>(e)))
    {
      return reduce<operator_::functor::imax>(std::forward<E>(e));
    }

    template <class E, class Opt>
    auto max(E &&e, Opt &&opt)
        -> decltype(reduce<operator_::functor::imax>(std::forward<E>(e),
                                                     std::forward<Opt>(opt)))
    {
      return reduce<operator_::functor::imax>(std::forward<E>(e),
                                              std::forward<Opt>(opt));
    }

    DEFINE_FUNCTOR(pythonic::numpy, max);
  }
}

#endif
