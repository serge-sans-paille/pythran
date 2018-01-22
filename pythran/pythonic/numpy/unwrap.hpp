#ifndef PYTHONIC_NUMPY_UNWRAP_HPP
#define PYTHONIC_NUMPY_UNWRAP_HPP

#include "pythonic/include/numpy/unwrap.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/int_.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/pi.hpp"

#include <boost/simd/function/max.hpp>
#include <boost/simd/function/abs.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace
  {
    template <class I0, class I1>
    void _unwrap(I0 ibegin, I0 iend, I1 obegin, double discont, utils::int_<1>)
    {
      *obegin = *ibegin;
      ++ibegin;
      for (; ibegin != iend; ++ibegin, ++obegin) {
        if (boost::simd::abs(*obegin - *ibegin) > discont)
          *(obegin + 1) =
              *ibegin + 2 * pi * int((*obegin - *ibegin) / (discont));
        else
          *(obegin + 1) = *ibegin;
      }
    }

    template <class I0, class I1, size_t N>
    void _unwrap(I0 ibegin, I0 iend, I1 obegin, double discont, utils::int_<N>)
    {
      for (; ibegin != iend; ++ibegin, ++obegin)
        _unwrap((*ibegin).begin(), (*ibegin).end(), (*obegin).begin(), discont,
                utils::int_<N - 1>());
    }
  }

  template <class E>
  types::ndarray<double, E::value> unwrap(E const &expr, double discont)
  {
    discont = boost::simd::max(discont, pi);
    types::ndarray<double, E::value> out(expr.shape(), __builtin__::None);
    _unwrap(expr.begin(), expr.end(), out.begin(), discont,
            utils::int_<E::value>());
    return out;
  }

  DEFINE_FUNCTOR(pythonic::numpy, unwrap)
}
PYTHONIC_NS_END

#endif
