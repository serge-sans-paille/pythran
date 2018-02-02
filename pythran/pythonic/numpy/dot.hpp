#ifndef PYTHONIC_NUMPY_DOT_HPP
#define PYTHONIC_NUMPY_DOT_HPP

#include "pythonic/include/numpy/dot.hpp"

#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/sum.hpp"
#include "pythonic/types/numpy_expr.hpp"
#include "pythonic/types/traits.hpp"

#if defined(PYTHRAN_BLAS_ATLAS)
extern "C" {
#endif
#include <cblas.h>
#if defined(PYTHRAN_BLAS_ATLAS)
}
#endif

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class E, class F>
  typename std::enable_if<types::is_dtype<E>::value &&
                              types::is_dtype<F>::value,
                          decltype(std::declval<E>() * std::declval<F>())>::type
  dot(E const &e, F const &f)
  {
    return e * f;
  }

  template <class E, class F>
  typename std::enable_if<
      types::is_numexpr_arg<E>::value &&
          types::is_numexpr_arg<F>::value    // Arguments are array_like
          && E::value == 1 && F::value == 1, // It is a two vectors.
      typename __combined<typename E::dtype, typename F::dtype>::type>::type
  dot(E const &e, F const &f)
  {
    return sum(types::numpy_expr<operator_::functor::mul, E, F>(e, f));
  }

/// Matrice / Vector multiplication

#define MV_DEF(T, L)                                                           \
  void mv(int m, int n, T *A, T *B, T *C)                                      \
  {                                                                            \
    cblas_##L##gemv(CblasRowMajor, CblasNoTrans, n, m, 1, A, m, B, 1, 0, C,    \
                    1);                                                        \
  }

  MV_DEF(double, d)
  MV_DEF(float, s)

#undef MV_DEF
#define MV_DEF(T, K, L)                                                        \
  void mv(int m, int n, T *A, T *B, T *C)                                      \
  {                                                                            \
    T alpha = 1, beta = 0;                                                     \
    cblas_##L##gemv(CblasRowMajor, CblasNoTrans, n, m, (K *)&alpha, (K *)A, m, \
                    (K *)B, 1, (K *)&beta, (K *)C, 1);                         \
  }
  MV_DEF(std::complex<float>, float, c)
  MV_DEF(std::complex<double>, double, z)
#undef MV_DEF

  template <class E>
  typename std::enable_if<is_blas_type<E>::value, types::ndarray<E, 1>>::type
      dot(types::ndarray<E, 2> const &f, types::ndarray<E, 1> const &e)
  {
    types::ndarray<E, 1> out(types::array<long, 1>{{f.shape()[0]}},
                             __builtin__::None);
    const int m = f.shape()[1], n = f.shape()[0];
    mv(m, n, f.buffer, e.buffer, out.buffer);
    return out;
  }

// The trick is to ! transpose the matrix so that MV become VM
#define VM_DEF(T, L)                                                           \
  void vm(int m, int n, T *A, T *B, T *C)                                      \
  {                                                                            \
    cblas_##L##gemv(CblasRowMajor, CblasTrans, n, m, 1, A, m, B, 1, 0, C, 1);  \
  }

  VM_DEF(double, d)
  VM_DEF(float, s)

#undef VM_DEF
#define VM_DEF(T, K, L)                                                        \
  void vm(int m, int n, T *A, T *B, T *C)                                      \
  {                                                                            \
    T alpha = 1, beta = 0;                                                     \
    cblas_##L##gemv(CblasRowMajor, CblasTrans, n, m, (K *)&alpha, (K *)A, m,   \
                    (K *)B, 1, (K *)&beta, (K *)C, 1);                         \
  }
  VM_DEF(std::complex<float>, float, c)
  VM_DEF(std::complex<double>, double, z)
#undef VM_DEF

  template <class E>
  typename std::enable_if<is_blas_type<E>::value, types::ndarray<E, 1>>::type
      dot(types::ndarray<E, 1> const &e, types::ndarray<E, 2> const &f)
  {
    types::ndarray<E, 1> out(types::array<long, 1>{{f.shape()[1]}},
                             __builtin__::None);
    const int m = f.shape()[1], n = f.shape()[0];
    vm(m, n, f.buffer, e.buffer, out.buffer);
    return out;
  }

  // If arguments could be use with blas, we evaluate them as we need pointer
  // on array for blas
  template <class E, class F>
  typename std::enable_if<
      types::is_numexpr_arg<E>::value &&
          types::is_numexpr_arg<F>::value // It is an array_like
          && !(types::is_ndarray<E>::value && types::is_ndarray<F>::value) &&
          is_blas_type<typename E::dtype>::value &&
          is_blas_type<typename F::dtype>::value // With dtype compatible with
                                                 // blas
          &&
          E::value == 2 && F::value == 1, // And it is matrix / vect
      types::ndarray<
          typename __combined<typename E::dtype, typename F::dtype>::type,
          1>>::type
  dot(E const &e, F const &f)
  {
    types::ndarray<
        typename __combined<typename E::dtype, typename F::dtype>::type, 2> e_ =
        e;
    types::ndarray<
        typename __combined<typename E::dtype, typename F::dtype>::type, 1> f_ =
        f;
    return dot(e_, f_);
  }

  // If arguments could be use with blas, we evaluate them as we need pointer
  // on array for blas
  template <class E, class F>
  typename std::enable_if<
      types::is_numexpr_arg<E>::value &&
          types::is_numexpr_arg<F>::value // It is an array_like
          && !(types::is_ndarray<E>::value && types::is_ndarray<F>::value) &&
          is_blas_type<typename E::dtype>::value &&
          is_blas_type<typename F::dtype>::value // With dtype compatible with
                                                 // blas
          &&
          E::value == 1 && F::value == 2, // And it is vect / matrix
      types::ndarray<
          typename __combined<typename E::dtype, typename F::dtype>::type,
          1>>::type
  dot(E const &e, F const &f)
  {
    types::ndarray<
        typename __combined<typename E::dtype, typename F::dtype>::type, 1> e_ =
        e;
    types::ndarray<
        typename __combined<typename E::dtype, typename F::dtype>::type, 2> f_ =
        f;
    return dot(e_, f_);
  }

  // If one of the arg doesn't have a "blas compatible type", we use a slow
  // matrix vector multiplication.
  template <class E, class F>
  typename std::enable_if<
      (!is_blas_type<typename E::dtype>::value ||
       !is_blas_type<typename F::dtype>::value) &&
          E::value == 1 && F::value == 2, // And it is vect / matrix
      types::ndarray<
          typename __combined<typename E::dtype, typename F::dtype>::type,
          1>>::type
  dot(E const &e, F const &f)
  {
    types::ndarray<
        typename __combined<typename E::dtype, typename F::dtype>::type, 1>
    out(types::array<long, 1>{{f.shape()[1]}}, 0);
    for (long i = 0; i < out.shape()[0]; i++)
      for (long j = 0; j < f.shape()[0]; j++)
        out[i] += e[j] * f[types::array<long, 2>{{j, i}}];
    return out;
  }

  // If one of the arg doesn't have a "blas compatible type", we use a slow
  // matrix vector multiplication.
  template <class E, class F>
  typename std::enable_if<
      (!is_blas_type<typename E::dtype>::value ||
       !is_blas_type<typename F::dtype>::value) &&
          E::value == 2 && F::value == 1, // And it is vect / matrix
      types::ndarray<
          typename __combined<typename E::dtype, typename F::dtype>::type,
          1>>::type
  dot(E const &e, F const &f)
  {
    types::ndarray<
        typename __combined<typename E::dtype, typename F::dtype>::type, 1>
    out(types::array<long, 1>{{e.shape()[0]}}, 0);
    for (long i = 0; i < out.shape()[0]; i++)
      for (long j = 0; j < f.shape()[0]; j++)
        out[i] += e[types::array<long, 2>{{i, j}}] * f[j];
    return out;
  }

/// Matrix / Matrix multiplication

#define MM_DEF(T, L)                                                           \
  void mm(int m, int n, int k, T *A, T *B, T *C)                               \
  {                                                                            \
    cblas_##L##gemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k, 1, A,  \
                    k, B, n, 0, C, n);                                         \
  }
  MM_DEF(double, d)
  MM_DEF(float, s)
#undef MM_DEF
#define MM_DEF(T, K, L)                                                        \
  void mm(int m, int n, int k, T *A, T *B, T *C)                               \
  {                                                                            \
    T alpha = 1, beta = 0;                                                     \
    cblas_##L##gemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k,        \
                    (K *)&alpha, (K *)A, k, (K *)B, n, (K *)&beta, (K *)C, n); \
  }
  MM_DEF(std::complex<float>, float, c)
  MM_DEF(std::complex<double>, double, z)
#undef MM_DEF

  template <class E>
  typename std::enable_if<is_blas_type<E>::value, types::ndarray<E, 2>>::type
      dot(types::ndarray<E, 2> const &a, types::ndarray<E, 2> const &b)
  {
    int n = b.shape()[1], m = a.shape()[0], k = b.shape()[0];

    types::ndarray<E, 2> out(types::array<long, 2>{{m, n}}, __builtin__::None);
    mm(m, n, k, a.buffer, b.buffer, out.buffer);
    return out;
  }

  template <class E>
  typename std::enable_if<is_blas_type<E>::value, types::ndarray<E, 2>>::type &
      dot(types::ndarray<E, 2> const &a, types::ndarray<E, 2> const &b,
          types::ndarray<E, 2> &c)
  {
    int n = b.shape()[1], m = a.shape()[0], k = b.shape()[0];

    mm(m, n, k, a.buffer, b.buffer, c.buffer);
    return c;
  }

#define TM_DEF(T, L)                                                           \
  void tm(int m, int n, int k, T *A, T *B, T *C)                               \
  {                                                                            \
    cblas_##L##gemm(CblasRowMajor, CblasTrans, CblasNoTrans, m, n, k, 1, A, m, \
                    B, n, 0, C, n);                                            \
  }
  TM_DEF(double, d)
  TM_DEF(float, s)
#undef TM_DEF
#define TM_DEF(T, K, L)                                                        \
  void tm(int m, int n, int k, T *A, T *B, T *C)                               \
  {                                                                            \
    T alpha = 1, beta = 0;                                                     \
    cblas_##L##gemm(CblasRowMajor, CblasTrans, CblasNoTrans, m, n, k,          \
                    (K *)&alpha, (K *)A, m, (K *)B, n, (K *)&beta, (K *)C, n); \
  }
  TM_DEF(std::complex<float>, float, c)
  TM_DEF(std::complex<double>, double, z)
#undef TM_DEF

  template <class E>
  typename std::enable_if<is_blas_type<E>::value, types::ndarray<E, 2>>::type
      dot(types::numpy_texpr<types::ndarray<E, 2>> const &a,
          types::ndarray<E, 2> const &b)
  {
    int n = b.shape()[1], m = a.shape()[0], k = a.shape()[1];

    types::ndarray<E, 2> out(types::array<long, 2>{{m, n}}, __builtin__::None);
    tm(m, n, k, a.arg.buffer, b.buffer, out.buffer);
    return out;
  }

#define MT_DEF(T, L)                                                           \
  void mt(int m, int n, int k, T *A, T *B, T *C)                               \
  {                                                                            \
    cblas_##L##gemm(CblasRowMajor, CblasNoTrans, CblasTrans, m, n, k, 1, A, k, \
                    B, k, 0, C, n);                                            \
  }
  MT_DEF(double, d)
  MT_DEF(float, s)
#undef MT_DEF
#define MT_DEF(T, K, L)                                                        \
  void mt(int m, int n, int k, T *A, T *B, T *C)                               \
  {                                                                            \
    T alpha = 1, beta = 0;                                                     \
    cblas_##L##gemm(CblasRowMajor, CblasNoTrans, CblasTrans, m, n, k,          \
                    (K *)&alpha, (K *)A, k, (K *)B, k, (K *)&beta, (K *)C, n); \
  }
  MT_DEF(std::complex<float>, float, c)
  MT_DEF(std::complex<double>, double, z)
#undef MT_DEF

  template <class E>
  typename std::enable_if<is_blas_type<E>::value, types::ndarray<E, 2>>::type
      dot(types::ndarray<E, 2> const &a,
          types::numpy_texpr<types::ndarray<E, 2>> const &b)
  {
    int n = b.shape()[1], m = a.shape()[0], k = b.shape()[0];

    types::ndarray<E, 2> out(types::array<long, 2>{{m, n}}, __builtin__::None);
    mt(m, n, k, a.buffer, b.arg.buffer, out.buffer);
    return out;
  }

#define TT_DEF(T, L)                                                           \
  void tt(int m, int n, int k, T *A, T *B, T *C)                               \
  {                                                                            \
    cblas_##L##gemm(CblasRowMajor, CblasTrans, CblasTrans, m, n, k, 1, A, m,   \
                    B, k, 0, C, n);                                            \
  }
  TT_DEF(double, d)
  TT_DEF(float, s)
#undef TT_DEF
#define TT_DEF(T, K, L)                                                        \
  void tt(int m, int n, int k, T *A, T *B, T *C)                               \
  {                                                                            \
    T alpha = 1, beta = 0;                                                     \
    cblas_##L##gemm(CblasRowMajor, CblasTrans, CblasTrans, m, n, k,            \
                    (K *)&alpha, (K *)A, m, (K *)B, k, (K *)&beta, (K *)C, n); \
  }
  TT_DEF(std::complex<float>, float, c)
  TT_DEF(std::complex<double>, double, z)
#undef TT_DEF

  template <class E>
  typename std::enable_if<is_blas_type<E>::value, types::ndarray<E, 2>>::type
      dot(types::numpy_texpr<types::ndarray<E, 2>> const &a,
          types::numpy_texpr<types::ndarray<E, 2>> const &b)
  {
    int n = b.shape()[1], m = a.shape()[0], k = b.shape()[0];

    types::ndarray<E, 2> out(types::array<long, 2>{{m, n}}, __builtin__::None);
    tt(m, n, k, a.arg.buffer, b.arg.buffer, out.buffer);
    return out;
  }

  // If arguments could be use with blas, we evaluate them as we need pointer
  // on array for blas
  template <class E, class F>
  typename std::enable_if<
      types::is_numexpr_arg<E>::value &&
          types::is_numexpr_arg<F>::value // It is an array_like
          && !(types::is_ndarray<E>::value && types::is_ndarray<F>::value) &&
          is_blas_type<typename E::dtype>::value &&
          is_blas_type<typename F::dtype>::value // With dtype compatible with
                                                 // blas
          &&
          E::value == 2 && F::value == 2, // And both are matrix
      types::ndarray<
          typename __combined<typename E::dtype, typename F::dtype>::type,
          2>>::type
  dot(E const &e, F const &f)
  {
    types::ndarray<
        typename __combined<typename E::dtype, typename F::dtype>::type, 2> e_ =
        e;
    types::ndarray<
        typename __combined<typename E::dtype, typename F::dtype>::type, 2> f_ =
        f;
    return dot(e_, f_);
  }

  // If one of the arg doesn't have a "blas compatible type", we use a slow
  // matrix multiplication.
  template <class E, class F>
  typename std::enable_if<
      (!is_blas_type<typename E::dtype>::value ||
       !is_blas_type<typename F::dtype>::value) &&
          E::value == 2 && F::value == 2, // And it is matrix / matrix
      types::ndarray<
          typename __combined<typename E::dtype, typename F::dtype>::type,
          2>>::type
  dot(E const &e, F const &f)
  {
    types::ndarray<
        typename __combined<typename E::dtype, typename F::dtype>::type, 2>
    out(types::array<long, 2>{{e.shape()[0], f.shape()[1]}}, 0);
    for (long i = 0; i < out.shape()[0]; i++)
      for (long j = 0; j < out.shape()[1]; j++)
        for (long k = 0; k < e.shape()[1]; k++)
          out[types::array<long, 2>{{i, j}}] +=
              e[types::array<long, 2>{{i, k}}] *
              f[types::array<long, 2>{{k, j}}];
    return out;
  }

  DEFINE_FUNCTOR(pythonic::numpy, dot);
}
PYTHONIC_NS_END

#endif
