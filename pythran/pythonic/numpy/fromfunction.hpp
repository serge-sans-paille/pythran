#ifndef PYTHONIC_NUMPY_FROMFUNCTION_HPP
#define PYTHONIC_NUMPY_FROMFUNCTION_HPP

#include "pythonic/include/numpy/fromfunction.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/None.hpp"
#include "pythonic/utils/tags.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class F, size_t N, class dtype, class Tags>
  struct fromfunction_helper;

  template <class F, class dtype, class purity_tag>
  template <class pS>
  types::ndarray<typename std::remove_cv<typename std::remove_reference<
                     typename std::result_of<F(dtype)>::type>::type>::type,
                 pS> fromfunction_helper<F, 1, dtype, purity_tag>::
  operator()(F &&f, pS const &shape, dtype d)
  {
    types::ndarray<typename std::remove_cv<typename std::remove_reference<
                       typename std::result_of<F(dtype)>::type>::type>::type,
                   pS> out(shape, __builtin__::None);
    long n = std::get<0>(out.shape());
#ifdef _OPENMP
    if (std::is_same<purity_tag, purity::pure_tag>::value &&
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
  template <class pS>
  types::ndarray<
      typename std::remove_cv<typename std::remove_reference<
          typename std::result_of<F(dtype, dtype)>::type>::type>::type,
      pS> fromfunction_helper<F, 2, dtype, purity_tag>::
  operator()(F &&f, pS const &shape, dtype d)
  {
    types::ndarray<
        typename std::remove_cv<typename std::remove_reference<
            typename std::result_of<F(dtype, dtype)>::type>::type>::type,
        pS> out(shape, __builtin__::None);
    auto &&out_shape = out.shape();
    long n = std::get<0>(out_shape);
    long m = std::get<1>(out_shape);
#ifdef _OPENMP
    if (std::is_same<purity_tag, purity::pure_tag>::value &&
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

  template <class F, class pS, class dtype>
  auto fromfunction(F &&f, pS const &shape, dtype d)
      -> decltype(fromfunction_helper<F, std::tuple_size<pS>::value, dtype,
                                      typename pythonic::purity_of<F>::type>()(
          std::forward<F>(f), shape))
  {
    return fromfunction_helper<F, std::tuple_size<pS>::value, dtype,
                               typename pythonic::purity_of<F>::type>()(
        std::forward<F>(f), shape);
  }

  /* TODO: must specialize for higher order */
}
PYTHONIC_NS_END

#endif
