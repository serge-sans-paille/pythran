#ifndef PYTHONIC_NUMPY_DIFF_HPP
#define PYTHONIC_NUMPY_DIFF_HPP

#include "pythonic/include/numpy/diff.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/asarray.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class E>
    types::ndarray<typename E::dtype, E::value> diff(E const &expr, long n)
    {
      auto arr = asarray(expr);
      auto shape = expr.shape();
      --shape[E::value - 1];

      types::ndarray<typename E::dtype, E::value> out(shape, __builtin__::None);
      auto slice = expr.shape()[E::value - 1];
      auto iter = arr.fbegin();
      auto out_iter = out.fbegin();
      for (long i = 0, sz = expr.flat_size(); i < sz; i += slice) {
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
        return diff(
            out, n - 1); // TODO: inplace modification to avoid n-1 allocations
    }

    DEFINE_FUNCTOR(pythonic::numpy, diff);
  }
}

#endif
