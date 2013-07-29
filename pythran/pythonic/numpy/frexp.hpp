#ifndef PYTHONIC_NUMPY_FREXP_HPP
#define PYTHONIC_NUMPY_FREXP_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/traits.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T>
            typename std::enable_if<std::is_scalar<T>::value, std::tuple<T,int>>::type
            frexp(T val) {
                int exp;
                T significand = std::frexp(val, &exp);
                return std::make_tuple(significand, exp);
            }
        template<class E>
            typename std::enable_if<
            not std::is_scalar<E>::value and not types::is_complex<E>::value,
                std::tuple<
                    types::ndarray<typename types::numpy_expr_to_ndarray<E>::type::dtype, types::numpy_expr_to_ndarray<E>::N>,
                types::ndarray<int, types::numpy_expr_to_ndarray<E>::N>
                    >
                    >::type
                    frexp(E const& arr) {
                        types::ndarray<typename types::numpy_expr_to_ndarray<E>::type::dtype, types::numpy_expr_to_ndarray<E>::N> significands(arr.shape, __builtin__::None);
                        types::ndarray<int, types::numpy_expr_to_ndarray<E>::N> exps(arr.shape, __builtin__::None);
                        for(long i=0,n=arr.size(); i<n; ++i)
                            significands.buffer[i] = std::frexp(arr.at(i), exps.buffer + i);
                        return std::make_tuple(significands, exps);
                    }
        PROXY(pythonic::numpy, frexp);

    }

}

#endif

