#ifndef PYTHONIC_INCLUDE_NUMPY_SUM_HPP
#define PYTHONIC_INCLUDE_NUMPY_SUM_HPP

#include "pythonic/include/numpy/reduce.hpp"
#include "pythonic/include/operator_/iadd.hpp"
#include "pythonic/include/utils/functor.hpp"

#ifdef USE_BOOST_SIMD
#include <boost/simd/include/functions/sum.hpp>
#endif

namespace pythonic
{

  namespace numpy
  {

    template <class E>
    auto sum(E &&e)
        -> decltype(reduce<operator_::functor::iadd>(std::forward<E>(e)));

    template <class E, class Opt>
    auto sum(E &&e, Opt &&opt)
        -> decltype(reduce<operator_::functor::iadd>(std::forward<E>(e),
                                                     std::forward<Opt>(opt)));

    DECLARE_FUNCTOR(pythonic::numpy, sum);
  }
}

#endif
