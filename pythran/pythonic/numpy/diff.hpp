#ifndef PYTHONIC_NUMPY_DIFF_HPP
#define PYTHONIC_NUMPY_DIFF_HPP

#include "pythonic/include/numpy/diff.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/asarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace details
  {
    template <class E>
    types::ndarray<typename E::dtype, types::array<long, E::value>>
    diff(E const &arr, long n)
    {
      auto shape = sutils::array(arr.shape());
      --shape[E::value - 1];
      auto out = arr.reshape(
          shape); // this does not leak, but uses slightly too much memory

      auto slice = std::get<E::value - 1>(arr.shape());
      auto iter = arr.fbegin();
      auto out_iter = out.fbegin();
      for (long i = 0, sz = arr.flat_size(); i < sz; i += slice) {
        auto prev = *(iter + i);
        for (long k = 1; k < slice; ++k, ++out_iter) {
          auto nprev = *(iter + i + k);
          *(out_iter) = nprev - prev;
          prev = nprev;
        }
      }
      if (n == 1)
        return out;
      else
        return diff(out, n - 1);
    }
  }
  template <class E>
  types::ndarray<typename E::dtype, types::array<long, E::value>>
  diff(E const &expr, long n)
  {
    return details::diff(array(expr),
                         n); // that's the only allocation that should happen
  }
}
PYTHONIC_NS_END

#endif
