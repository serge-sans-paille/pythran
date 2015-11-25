#ifndef PYTHONIC_NUMPY_ARGWHERE_HPP
#define PYTHONIC_NUMPY_ARGWHERE_HPP

#include "pythonic/include/numpy/argwhere.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/asarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    typename types::ndarray<long, 2> argwhere(E const &expr)
    {
      using out_type = typename types::ndarray<long, 2>;
      constexpr long N = E::value;
      auto arr = asarray(expr);
      long sz = arr.flat_size();
      auto eshape = arr.shape();

      long *buffer =
          (long *)malloc(sz * N * sizeof(long)); // too much memory used
      long *buffer_iter = buffer;

      long real_sz = 0;
      auto iter = arr.fbegin();
      for (long i = 0; i < sz; ++i, ++iter) {
        if (*iter) {
          ++real_sz;
          long mult = 1;
          for (long j = N - 1; j > 0; j--) {
            buffer_iter[j] = (i / mult) % eshape[j];
            mult *= eshape[j];
          }
          buffer_iter[0] = i / mult;
          buffer_iter += N;
        }
      }
      long shape[2] = {real_sz, N};
      return out_type(buffer, shape);
    }

    DEFINE_FUNCTOR(pythonic::numpy, argwhere);
  }
}

#endif
