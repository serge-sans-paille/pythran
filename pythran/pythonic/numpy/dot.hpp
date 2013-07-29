#ifndef PYTHONIC_NUMPY_DOT_HPP
#define PYTHONIC_NUMPY_DOT_HPP

#include "pythonic/numpy/asarray.hpp"
#include "pythonic/numpy/sum.hpp"
#include "pythonic/types/traits.hpp"

namespace pythonic {

    namespace numpy {
        template<class E, class F>
            typename std::enable_if<
            (std::is_scalar<E>::value or types::is_complex<E>::value) and (std::is_scalar<F>::value or types::is_complex<F>::value),
            decltype(std::declval<E>()*std::declval<F>())
                >::type
                dot(E const& e, F const& f)
                {
                    return e*f;
                }

        template<class E, class F>
            typename std::enable_if<
            types::is_array<E>::value and types::is_array<F>::value and
            types::numpy_expr_to_ndarray<E>::N == 1 and types::numpy_expr_to_ndarray<F>::N ==1,
            decltype(std::declval<typename types::numpy_expr_to_ndarray<E>::type::dtype>()*std::declval<typename types::numpy_expr_to_ndarray<F>::type::dtype>())
                >::type
                dot(E const& e, F const& f) {
                    return sum(e*f);
                }

        template<class E, class F>
            typename std::enable_if<
            (std::is_scalar<E>::value or types::is_complex<E>::value) and (std::is_scalar<E>::value or types::is_complex<E>::value),
            decltype(std::declval<E>()*std::declval<F>())
                >::type
                dot(types::list<E> const& e, types::list<F> const& f) {
                    return dot(asarray(e), asarray(f));
                }

        template<class E, class F>
            typename std::enable_if<
            (std::is_scalar<E>::value or types::is_complex<E>::value) and
            types::is_array<F>::value and types::numpy_expr_to_ndarray<F>::N ==1,
            decltype(std::declval<E>()*std::declval<typename types::numpy_expr_to_ndarray<F>::type::dtype>())
                >::type
                dot(F const& f,types::list<E> const& e) {
                    return dot(f, asarray(e));
                }

        template<class E, class F>
            typename std::enable_if<
            (std::is_scalar<E>::value or types::is_complex<E>::value) and
            types::is_array<F>::value and types::numpy_expr_to_ndarray<F>::N ==1,
            decltype(std::declval<E>()*std::declval<typename types::numpy_expr_to_ndarray<F>::type::dtype>())
                >::type
                dot(types::list<E> const& e, F const& f) {
                    return dot(asarray(e), f);
                }

        PROXY(pythonic::numpy, dot);

    }

}

#endif

