#ifndef PYTHONIC_NUMPY_MIN_HPP
#define PYTHONIC_NUMPY_MIN_HPP

#include "pythonic/include/numpy/min.hpp"

#include "pythonic/numpy/reduce.hpp"
#include "pythonic/operator_/imin.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class E>
    auto min(E &&e)
        -> decltype(reduce<operator_::proxy::imin>(std::forward<E>(e)))
    {
      return reduce<operator_::proxy::imin>(std::forward<E>(e));
    }

    template <class E, class Opt>
    auto min(E &&e, Opt &&opt)
        -> decltype(reduce<operator_::proxy::imin>(std::forward<E>(e),
                                                   std::forward<Opt>(opt)))
    {
      return reduce<operator_::proxy::imin>(std::forward<E>(e),
                                            std::forward<Opt>(opt));
    }

    PROXY_IMPL(pythonic::numpy, min);
  }
}

#endif
