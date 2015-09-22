#ifndef PYTHONIC_INCLUDE_NUMPY_PROD_HPP
#define PYTHONIC_INCLUDE_NUMPY_PROD_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/numpy/reduce.hpp"
#include "pythonic/include/operator_/imul.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class E>
    auto prod(E &&e)
        -> decltype(reduce<operator_::proxy::imul>(std::forward<E>(e)));

    template <class E, class Opt>
    auto prod(E &&e, Opt &&opt)
        -> decltype(reduce<operator_::proxy::imul>(std::forward<E>(e),
                                                   std::forward<Opt>(opt)));

    PROXY_DECL(pythonic::numpy, prod);
  }
}

#endif
