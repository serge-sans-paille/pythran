#ifndef PYTHONIC_NUMPY_FROMFUNCTION_HPP
#define PYTHONIC_NUMPY_FROMFUNCTION_HPP

#include "pythonic/include/numpy/fromfunction.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/None.hpp"
#include "pythonic/utils/tags.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class F, size_t N, class dtype, class Tags>
    struct fromfunction_helper;

    template <class F, class dtype, class purity_tag>
    types::ndarray<typename std::remove_cv<typename std::remove_reference<
                       typename std::result_of<F(dtype)>::type>::type>::type,
                   1> fromfunction_helper<F, 1, dtype, purity_tag>::
    operator()(F &&f, types::array<long, 1> const &shape, dtype d)
    {
      types::ndarray<typename std::remove_cv<typename std::remove_reference<
                         typename std::result_of<F(dtype)>::type>::type>::type,
                     1> out(shape, __builtin__::None);
      long n = out.shape()[0];
#ifdef _OPENMP
      if (std::is_same<purity_tag, purity::pure_tag>::value and
          n >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
#pragma omp parallel for
        for (long i = 0; i < n; ++i)
          out[i] = f(i);
      else
#endif
        for (long i = 0; i < n; ++i)
          out[i] = f(i);
      return out;
    }

    template <class F, class dtype, class purity_tag>
    types::ndarray<
        typename std::remove_cv<typename std::remove_reference<
            typename std::result_of<F(dtype, dtype)>::type>::type>::type,
        2> fromfunction_helper<F, 2, dtype, purity_tag>::
    operator()(F &&f, types::array<long, 2> const &shape, dtype d)
    {
      types::ndarray<
          typename std::remove_cv<typename std::remove_reference<
              typename std::result_of<F(dtype, dtype)>::type>::type>::type,
          2> out(shape, __builtin__::None);
      auto &&out_shape = out.shape();
      long n = out_shape[0];
      long m = out_shape[1];
#ifdef _OPENMP
      if (std::is_same<purity_tag, purity::pure_tag>::value and
          (m * n) >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
#pragma omp parallel for collapse(2)
        for (long i = 0; i < n; ++i)
          for (long j = 0; j < m; ++j)
            out[i][j] = f(i, j);
      else
#endif
        for (long i = 0; i < n; ++i)
          for (long j = 0; j < m; ++j)
            out[i][j] = f(i, j);
      return out;
    }

    template <class F, size_t N, class dtype>
    auto fromfunction(F &&f, types::array<long, N> const &shape, dtype d)
        -> decltype(fromfunction_helper<
            F, N, dtype, typename pythonic::purity_of<F>::type>()(
            std::forward<F>(f), shape))
    {
      return fromfunction_helper<F, N, dtype,
                                 typename pythonic::purity_of<F>::type>()(
          std::forward<F>(f), shape);
    }

    /* TODO: must specialize for higher order */
    DEFINE_FUNCTOR(pythonic::numpy, fromfunction);
  }
}

#endif
