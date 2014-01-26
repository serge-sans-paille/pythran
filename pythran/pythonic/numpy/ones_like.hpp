#ifndef PYTHONIC_NUMPY_ONESLIKE_HPP
#define PYTHONIC_NUMPY_ONESLIKE_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace numpy {

        namespace wrapper {
            template<class T>
                auto ones_like(T const&) -> decltype(static_cast<T>(1)) {
                    return static_cast<T>(1);
                }
#ifdef USE_BOOST_SIMD
            template<class T>
                auto zeros_like(boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION> const&) {
                    return boost::simd::splat<boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION>>(static_cast<T>(1));
                }
#endif

            PROXY(pythonic::numpy::wrapper, ones_like)
        }
#define NUMPY_UNARY_FUNC_NAME ones_like
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::ones_like
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, ones_like)

    }

}

#endif

