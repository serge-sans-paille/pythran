#ifndef PYTHONIC_NUMPY_ZEROSLIKE_HPP
#define PYTHONIC_NUMPY_ZEROSLIKE_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace numpy {

        namespace wrapper {
            template<class T>
                auto zeros_like(T const&) -> decltype(static_cast<T>(0)) {
                    return static_cast<T>(0);
                }
#ifdef USE_BOOST_SIMD
            template<class T>
                auto zeros_like(boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION> const&) {
                    return boost::simd::splat<boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION>>(static_cast<T>(0));
                }
#endif
            PROXY(pythonic::numpy::wrapper, zeros_like)
        }

#define NUMPY_UNARY_FUNC_NAME zeros_like
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::zeros_like
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, zeros_like)

    }

}

#endif

