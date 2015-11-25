#ifndef PYTHONIC_INCLUDE_NUMPY_DOT_HPP
#define PYTHONIC_INCLUDE_NUMPY_DOT_HPP

#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/numpy/sum.hpp"
#include "pythonic/include/types/numpy_expr.hpp"
#include "pythonic/include/types/traits.hpp"

#include <nt2/linalg/details/blas/mm.hpp>
#include <nt2/linalg/details/blas/mv.hpp>

template <class T>
struct is_blas_type : pythonic::types::is_complex<T> {
};

template <>
struct is_blas_type<float> : std::true_type {
};

template <>
struct is_blas_type<double> : std::true_type {
};

namespace pythonic
{

  namespace numpy
  {
    template <class E, class F>
    typename std::enable_if<
        types::is_dtype<E>::value and types::is_dtype<F>::value,
        decltype(std::declval<E>() * std::declval<F>())>::type
    dot(E const &e, F const &f);

    template <class E, class F>
    typename std::enable_if<
        types::is_numexpr_arg<E>::value and
            types::is_numexpr_arg<F>::value      // Arguments are array_like
            and E::value == 1 and F::value == 1, // It is a two vectors.
        typename __combined<typename E::dtype, typename F::dtype>::type>::type
    dot(E const &e, F const &f);

    /// Matrice / Vector multiplication

    // We transpose the matrix to reflect our C order
    template <class E>
    typename std::enable_if<is_blas_type<E>::value, types::ndarray<E, 1>>::type
        dot(types::ndarray<E, 2> const &f, types::ndarray<E, 1> const &e);

    // The trick is to not transpose the matrix so that MV become VM
    template <class E>
    typename std::enable_if<is_blas_type<E>::value, types::ndarray<E, 1>>::type
        dot(types::ndarray<E, 1> const &e, types::ndarray<E, 2> const &f);

    // If arguments could be use with blas, we evaluate them as we need pointer
    // on array for blas
    template <class E, class F>
    typename std::enable_if<
        types::is_numexpr_arg<E>::value and
            types::is_numexpr_arg<F>::value // It is an array_like
            and
            not(types::is_ndarray<E>::value and types::is_ndarray<F>::value) and
            is_blas_type<typename E::dtype>::value and
            is_blas_type<typename F::dtype>::value // With dtype compatible with
                                                   // blas
            and
            E::value == 2 and F::value == 1, // And it is matrix / vect
        types::ndarray<
            typename __combined<typename E::dtype, typename F::dtype>::type,
            1>>::type
    dot(E const &e, F const &f);

    // If arguments could be use with blas, we evaluate them as we need pointer
    // on array for blas
    template <class E, class F>
    typename std::enable_if<
        types::is_numexpr_arg<E>::value and
            types::is_numexpr_arg<F>::value // It is an array_like
            and
            not(types::is_ndarray<E>::value and types::is_ndarray<F>::value) and
            is_blas_type<typename E::dtype>::value and
            is_blas_type<typename F::dtype>::value // With dtype compatible with
                                                   // blas
            and
            E::value == 1 and F::value == 2, // And it is vect / matrix
        types::ndarray<
            typename __combined<typename E::dtype, typename F::dtype>::type,
            1>>::type
    dot(E const &e, F const &f);

    // If one of the arg doesn't have a "blas compatible type", we use a slow
    // matrix vector multiplication.
    template <class E, class F>
    typename std::enable_if<
        (not is_blas_type<typename E::dtype>::value or
         not is_blas_type<typename F::dtype>::value) and
            E::value == 1 and F::value == 2, // And it is vect / matrix
        types::ndarray<
            typename __combined<typename E::dtype, typename F::dtype>::type,
            1>>::type
    dot(E const &e, F const &f);

    // If one of the arg doesn't have a "blas compatible type", we use a slow
    // matrix vector multiplication.
    template <class E, class F>
    typename std::enable_if<
        (not is_blas_type<typename E::dtype>::value or
         not is_blas_type<typename F::dtype>::value) and
            E::value == 2 and F::value == 1, // And it is vect / matrix
        types::ndarray<
            typename __combined<typename E::dtype, typename F::dtype>::type,
            1>>::type
    dot(E const &e, F const &f);

    /// Matrix / Matrix multiplication

    // The trick is to use the transpose arguments to reflect C order.
    // We want to perform A * B in C order but blas order is F order.
    // So we compute B'A' == (AB)'. As this equality is perform with F order
    // We doesn't have to return a texpr because we want a C order matrice!!
    template <class E>
    typename std::enable_if<is_blas_type<E>::value, types::ndarray<E, 2>>::type
        dot(types::ndarray<E, 2> const &a, types::ndarray<E, 2> const &b);

    // If arguments could be sue with blas, we evaluate them as we need pointer
    // on array for blas
    template <class E, class F>
    typename std::enable_if<
        types::is_numexpr_arg<E>::value and
            types::is_numexpr_arg<F>::value // It is an array_like
            and
            not(types::is_ndarray<E>::value and types::is_ndarray<F>::value) and
            is_blas_type<typename E::dtype>::value and
            is_blas_type<typename F::dtype>::value // With dtype compatible with
                                                   // blas
            and
            E::value == 2 and F::value == 2, // And both are matrix
        types::ndarray<
            typename __combined<typename E::dtype, typename F::dtype>::type,
            2>>::type
    dot(E const &e, F const &f);

    // If one of the arg doesn't have a "blas compatible type", we use a slow
    // matrix multiplication.
    template <class E, class F>
    typename std::enable_if<
        (not is_blas_type<typename E::dtype>::value or
         not is_blas_type<typename F::dtype>::value) and
            E::value == 2 and F::value == 2, // And it is matrix / matrix
        types::ndarray<
            typename __combined<typename E::dtype, typename F::dtype>::type,
            2>>::type
    dot(E const &e, F const &f);

    DECLARE_FUNCTOR(pythonic::numpy, dot);
  }
}

#endif
