#ifndef PYTHONIC_NUMPY_PROD_HPP
#define PYTHONIC_NUMPY_PROD_HPP

#include "pythonic/include/numpy/prod.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/reduce.hpp"
#include "pythonic/operator_/imul.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class E>
    auto prod(E &&e)
        -> decltype(reduce<operator_::proxy::imul>(std::forward<E>(e)))
    {
      return reduce<operator_::proxy::imul>(std::forward<E>(e));
    }

    template <class E, class Opt>
    auto prod(E &&e, Opt &&opt)
        -> decltype(reduce<operator_::proxy::imul>(std::forward<E>(e),
                                                   std::forward<Opt>(opt)))
    {
      return reduce<operator_::proxy::imul>(std::forward<E>(e),
                                            std::forward<Opt>(opt));
    }

    PROXY_IMPL(pythonic::numpy, prod);
  }
}

#endif
