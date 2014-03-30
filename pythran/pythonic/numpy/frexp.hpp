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

        template<class E, class F, class G>
            void _frexp(E begin, E end, F significands_iter, G exps_iter, utils::int_<1>)
            {
                for(; begin != end; ++ begin, ++significands_iter, ++exps_iter)
                    *significands_iter = std::frexp(*begin, exps_iter);
            }
        template<class E, class F, class G, size_t N>
            void _frexp(E begin, E end, F significands_iter, G exps_iter, utils::int_<N>)
            {
                for(; begin != end; ++ begin, ++significands_iter, ++exps_iter)
                    _frexp((*begin).begin(), (*begin).end(), (*significands_iter).begin(), (*exps_iter).begin(), utils::int_<N-1>());
            }

        template<class E>
            typename std::enable_if<
                not std::is_scalar<E>::value and not types::is_complex<E>::value,
                std::tuple<typename types::numpy_expr_to_ndarray<E>::type,
                           types::ndarray<int, types::numpy_expr_to_ndarray<E>::N>>
            >::type
            frexp(E const& arr) {
                        typename types::numpy_expr_to_ndarray<E>::type significands(arr.shape, __builtin__::None);
                        types::ndarray<int, types::numpy_expr_to_ndarray<E>::N> exps(arr.shape, __builtin__::None);
                        _frexp(arr.begin(), arr.end(), significands.begin(), exps.begin(), utils::int_<E::value>());
                        return std::make_tuple(significands, exps);
                    }
        PROXY(pythonic::numpy, frexp);

    }

}

#endif

