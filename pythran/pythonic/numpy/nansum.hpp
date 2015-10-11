#ifndef PYTHONIC_NUMPY_NANSUM_HPP
#define PYTHONIC_NUMPY_NANSUM_HPP

#include "pythonic/include/numpy/nansum.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_type.hpp"
#include "pythonic/numpy/isnan.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E, class F>
    void _nansum(E begin, E end, F &sum, utils::int_<1>)
    {
      for (; begin != end; ++begin) {
        auto curr = *begin;
        if (not proxy::isnan()(curr))
          sum += curr;
      }
    }
    template <class E, class F, size_t N>
    void _nansum(E begin, E end, F &sum, utils::int_<N>)
    {
      for (; begin != end; ++begin)
        _nansum((*begin).begin(), (*begin).end(), sum, utils::int_<N - 1>());
    }

    template <class E>
    typename E::dtype nansum(E const &expr)
    {
      typename E::dtype s = 0;
      _nansum(expr.begin(), expr.end(), s, utils::int_<E::value>());
      return s;
    }

    PROXY_IMPL(pythonic::numpy, nansum);
  }
}

#endif
