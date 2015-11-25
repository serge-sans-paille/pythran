#ifndef PYTHONIC_INCLUDE_NUMPY_CUMPROD_HPP
#define PYTHONIC_INCLUDE_NUMPY_CUMPROD_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/numpy/partial_sum.hpp"
#include "pythonic/include/operator_/imul.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class E, class... Opts>
    auto cumprod(E &&e, Opts &&... opts)
        -> decltype(partial_sum<operator_::functor::imul>(
            std::forward<E>(e), std::forward<Opts>(opts)...));

    NUMPY_EXPR_TO_NDARRAY0_DECL(cumprod);

    DECLARE_FUNCTOR(pythonic::numpy, cumprod);
  }
}

#endif
