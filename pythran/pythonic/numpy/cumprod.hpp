#ifndef PYTHONIC_NUMPY_CUMPROD_HPP
#define PYTHONIC_NUMPY_CUMPROD_HPP

#include "pythonic/include/numpy/cumprod.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/partial_sum.hpp"
#include "pythonic/operator_/imul.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class E, class... Opts>
    auto cumprod(E &&e, Opts &&... opts)
        -> decltype(partial_sum<operator_::proxy::imul>(
            std::forward<E>(e), std::forward<Opts>(opts)...))
    {
      return partial_sum<operator_::proxy::imul>(std::forward<E>(e),
                                                 std::forward<Opts>(opts)...);
    }

    NUMPY_EXPR_TO_NDARRAY0_IMPL(cumprod);

    PROXY_IMPL(pythonic::numpy, cumprod);
  }
}

#endif
