#ifndef PYTHONIC_NUMPY_NANMAX_HPP
#define PYTHONIC_NUMPY_NANMAX_HPP

#include "pythonic/include/numpy/nanmax.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/ValueError.hpp"
#include "pythonic/numpy/isnan.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E, class F>
    void _nanmax(E begin, E end, F &max, utils::int_<1>)
    {
      for (; begin != end; ++begin) {
        auto curr = *begin;
        if (not functor::isnan()(curr) and curr > max)
          max = curr;
      }
    }
    template <class E, class F, size_t N>
    void _nanmax(E begin, E end, F &max, utils::int_<N>)
    {
      for (; begin != end; ++begin)
        _nanmax((*begin).begin(), (*begin).end(), max, utils::int_<N - 1>());
    }

    template <class E>
    typename E::dtype nanmax(E const &expr)
    {
      typename E::dtype max = std::numeric_limits<typename E::dtype>::lowest();
      _nanmax(expr.begin(), expr.end(), max, utils::int_<E::value>());
      return max;
    }

    DEFINE_FUNCTOR(pythonic::numpy, nanmax);
  }
}

#endif
