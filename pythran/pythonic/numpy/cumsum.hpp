#ifndef PYTHONIC_NUMPY_CUMSUM_HPP
#define PYTHONIC_NUMPY_CUMSUM_HPP

#include "pythonic/include/numpy/cumsum.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/numpy/partial_sum.hpp"
#include "pythonic/operator_/iadd.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class E, class... Opts>
    auto cumsum(E &&e, Opts &&... opts)
        -> decltype(partial_sum<operator_::functor::iadd>(
            std::forward<E>(e), std::forward<Opts>(opts)...))
    {
      return partial_sum<operator_::functor::iadd>(std::forward<E>(e),
                                                   std::forward<Opts>(opts)...);
    }

    DEFINE_FUNCTOR(pythonic::numpy, cumsum);
  }
}

#endif
