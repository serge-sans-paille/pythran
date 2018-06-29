#ifndef PYTHONIC_INCLUDE_NUMPY_DOT_HPP
#define PYTHONIC_INCLUDE_NUMPY_DOT_HPP

#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/numpy/sum.hpp"
#include "pythonic/include/types/numpy_expr.hpp"
#include "pythonic/include/types/traits.hpp"

template <class T>
struct is_blas_type : pythonic::types::is_complex<T> {
};

template <>
struct is_blas_type<float> : std::true_type {
};

template <>
struct is_blas_type<double> : std::true_type {
};

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class E, class F>
  typename std::enable_if<types::is_dtype<E>::value &&
                              types::is_dtype<F>::value,
                          decltype(std::declval<E>() * std::declval<F>())>::type
  dot(E const &e, F const &f);

  /// Vector / Vector multiplication
  template <class E, class F>
  typename std::enable_if<
      types::is_numexpr_arg<E>::value &&
          types::is_numexpr_arg<F>::value    // Arguments are array_like
          && E::value == 1 && F::value == 1, // It is a two vectors.
      typename __combined<typename E::dtype, typename F::dtype>::type>::type
  dot(E const &e, F const &f);

  template <class pS0, class pS1>
  typename std::enable_if<std::tuple_size<pS0>::value == 1 &&
                              std::tuple_size<pS1>::value == 1,
                          float>::type
  dot(types::ndarray<float, pS0> const &e, types::ndarray<float, pS1> const &f);
  template <class pS0, class pS1>
  typename std::enable_if<std::tuple_size<pS0>::value == 1 &&
                              std::tuple_size<pS1>::value == 1,
                          double>::type
  dot(types::ndarray<double, pS0> const &e,
      types::ndarray<double, pS1> const &f);

  /// Matrice / Vector multiplication

  // We transpose the matrix to reflect our C order
  template <class E, class pS0, class pS1>
  typename std::enable_if<is_blas_type<E>::value &&
                              std::tuple_size<pS0>::value == 2 &&
                              std::tuple_size<pS1>::value == 1,
                          types::ndarray<E, types::pshape<long>>>::type
  dot(types::ndarray<E, pS0> const &f, types::ndarray<E, pS1> const &e);

  // The trick is to ! transpose the matrix so that MV become VM
  template <class E, class pS0, class pS1>
  typename std::enable_if<is_blas_type<E>::value &&
                              std::tuple_size<pS0>::value == 1 &&
                              std::tuple_size<pS1>::value == 2,
                          types::ndarray<E, types::pshape<long>>>::type
  dot(types::ndarray<E, pS0> const &e, types::ndarray<E, pS1> const &f);

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
          types::pshape<long>>>::type
  dot(E const &e, F const &f);

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
          types::pshape<long>>>::type
  dot(E const &e, F const &f);

  // If one of the arg doesn't have a "blas compatible type", we use a slow
  // matrix vector multiplication.
  template <class E, class F>
  typename std::enable_if<
      (!is_blas_type<typename E::dtype>::value ||
       !is_blas_type<typename F::dtype>::value) &&
          E::value == 1 && F::value == 2, // And it is vect / matrix
      types::ndarray<
          typename __combined<typename E::dtype, typename F::dtype>::type,
          types::pshape<long>>>::type
  dot(E const &e, F const &f);

  // If one of the arg doesn't have a "blas compatible type", we use a slow
  // matrix vector multiplication.
  template <class E, class F>
  typename std::enable_if<
      (!is_blas_type<typename E::dtype>::value ||
       !is_blas_type<typename F::dtype>::value) &&
          E::value == 2 && F::value == 1, // And it is vect / matrix
      types::ndarray<
          typename __combined<typename E::dtype, typename F::dtype>::type,
          types::pshape<long>>>::type
  dot(E const &e, F const &f);

  /// Matrix / Matrix multiplication

  // The trick is to use the transpose arguments to reflect C order.
  // We want to perform A * B in C order but blas order is F order.
  // So we compute B'A' == (AB)'. As this equality is perform with F order
  // We doesn't have to return a texpr because we want a C order matrice!!
  template <class E, class pS0, class pS1>
  typename std::enable_if<is_blas_type<E>::value &&
                              std::tuple_size<pS0>::value == 2 &&
                              std::tuple_size<pS1>::value == 2,
                          types::ndarray<E, types::array<long, 2>>>::type
  dot(types::ndarray<E, pS0> const &a, types::ndarray<E, pS1> const &b);

  template <class E, class pS0, class pS1, class pS2>
  typename std::enable_if<
      is_blas_type<E>::value && std::tuple_size<pS0>::value == 2 &&
          std::tuple_size<pS1>::value == 2 && std::tuple_size<pS2>::value == 2,
      types::ndarray<E, pS2>>::type &
  dot(types::ndarray<E, pS0> const &a, types::ndarray<E, pS1> const &b,
      types::ndarray<E, pS2> &c);

  // If arguments could be sue with blas, we evaluate them as we need pointer
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
          types::array<long, 2>>>::type
  dot(E const &e, F const &f);

  // If one of the arg doesn't have a "blas compatible type", we use a slow
  // matrix multiplication.
  template <class E, class F>
  typename std::enable_if<
      (!is_blas_type<typename E::dtype>::value ||
       !is_blas_type<typename F::dtype>::value) &&
          E::value == 2 && F::value == 2, // And it is matrix / matrix
      types::ndarray<
          typename __combined<typename E::dtype, typename F::dtype>::type,
          types::array<long, 2>>>::type
  dot(E const &e, F const &f);

  DECLARE_FUNCTOR(pythonic::numpy, dot);
}
PYTHONIC_NS_END

#endif
