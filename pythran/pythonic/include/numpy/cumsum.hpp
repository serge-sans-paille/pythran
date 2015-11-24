#ifndef PYTHONIC_INCLUDE_NUMPY_CUMSUM_HPP
#define PYTHONIC_INCLUDE_NUMPY_CUMSUM_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/numpy/partial_sum.hpp"
#include "pythonic/include/operator_/iadd.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class E, class... Opts>
    auto cumsum(E &&e, Opts &&... opts)
        -> decltype(partial_sum<operator_::functor::iadd>(
            std::forward<E>(e), std::forward<Opts>(opts)...));

    DECLARE_FUNCTOR(pythonic::numpy, cumsum);
  }
}

#endif
