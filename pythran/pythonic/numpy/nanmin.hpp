#ifndef PYTHONIC_NUMPY_NANMIN_HPP
#define PYTHONIC_NUMPY_NANMIN_HPP

#include "pythonic/include/numpy/nanmin.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/ValueError.hpp"
#include "pythonic/numpy/isnan.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E, class F>
    void _nanmin(E begin, E end, F &min, utils::int_<1>)
    {
      for (; begin != end; ++begin) {
        auto curr = *begin;
        if (not functor::isnan()(curr) and curr < min)
          min = curr;
      }
    }

    template <class E, class F, size_t N>
    void _nanmin(E begin, E end, F &min, utils::int_<N>)
    {
      for (; begin != end; ++begin)
        _nanmin((*begin).begin(), (*begin).end(), min, utils::int_<N - 1>());
    }

    template <class E>
    typename E::dtype nanmin(E const &expr)
    {
      typename E::dtype min = std::numeric_limits<typename E::dtype>::max();
      _nanmin(expr.begin(), expr.end(), min, utils::int_<E::value>());
      return min;
    }

    DEFINE_FUNCTOR(pythonic::numpy, nanmin);
  }
}

#endif
