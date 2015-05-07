#ifndef PYTHONIC_INCLUDE_NUMPY_FREXP_HPP
#define PYTHONIC_INCLUDE_NUMPY_FREXP_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/traits.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T>
            typename std::enable_if<std::is_scalar<T>::value, std::tuple<T,int>>::type
            frexp(T val);

        template<class E, class F, class G>
            void _frexp(E begin, E end, F significands_iter, G exps_iter, utils::int_<1>);

        template<class E, class F, class G, size_t N>
            void _frexp(E begin, E end, F significands_iter, G exps_iter, utils::int_<N>);

        template<class E>
            typename std::enable_if<
                not std::is_scalar<E>::value and not types::is_complex<E>::value,
                std::tuple<typename types::numpy_expr_to_ndarray<E>::type,
                           types::ndarray<int, types::numpy_expr_to_ndarray<E>::N>>
            >::type
            frexp(E const& arr);

        PROXY_DECL(pythonic::numpy, frexp);

    }

}

#endif
