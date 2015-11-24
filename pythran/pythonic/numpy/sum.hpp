#ifndef PYTHONIC_NUMPY_SUM_HPP
#define PYTHONIC_NUMPY_SUM_HPP

#include "pythonic/include/numpy/sum.hpp"
#include "pythonic/numpy/reduce.hpp"
#include "pythonic/operator_/iadd.hpp"
#include "pythonic/utils/functor.hpp"

#ifdef USE_BOOST_SIMD
#include <boost/simd/include/functions/sum.hpp>
#endif

#include <algorithm>

namespace pythonic
{

  namespace numpy
  {

    template <class E>
    auto sum(E &&e)
        -> decltype(reduce<operator_::functor::iadd>(std::forward<E>(e)))
    {
      return reduce<operator_::functor::iadd>(std::forward<E>(e));
    }

    template <class E, class Opt>
    auto sum(E &&e, Opt &&opt)
        -> decltype(reduce<operator_::functor::iadd>(std::forward<E>(e),
                                                     std::forward<Opt>(opt)))
    {
      return reduce<operator_::functor::iadd>(std::forward<E>(e),
                                              std::forward<Opt>(opt));
    }

    DEFINE_FUNCTOR(pythonic::numpy, sum);
  }
}

#endif
