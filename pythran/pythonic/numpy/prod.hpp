#ifndef PYTHONIC_NUMPY_PROD_HPP
#define PYTHONIC_NUMPY_PROD_HPP

#include "pythonic/include/numpy/prod.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/numpy/reduce.hpp"
#include "pythonic/operator_/imul.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class... Args>
    auto prod(Args &&... args) -> decltype(
        reduce<operator_::functor::imul>(std::forward<Args>(args)...))
    {
      return reduce<operator_::functor::imul>(std::forward<Args>(args)...);
    }

    DEFINE_FUNCTOR(pythonic::numpy, prod);
  }
}

#endif
