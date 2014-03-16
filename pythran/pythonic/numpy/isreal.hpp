#ifndef PYTHONIC_NUMPY_ISREAL_HPP
#define PYTHONIC_NUMPY_ISREAL_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/traits.hpp"

namespace pythonic {

    namespace numpy {

        //TODO could be a unary_expr
        template<class I, class O>
            void _isreal(I begin, I end, O obegin, utils::int_<1>)
            {
                for(; begin != end; ++begin, ++obegin)
                    *obegin = (*begin).imag() == 0.;
            }
        template<class I, class O, size_t N>
            void _isreal(I begin, I end, O obegin, utils::int_<N>)
            {
                for(; begin != end; ++begin, ++obegin)
                    _isreal((*begin).begin(), (*begin).end(), (*obegin).begin(), utils::int_<N-1>());
            }

        template<class E>
            typename std::enable_if<types::is_complex<typename types::numpy_expr_to_ndarray<E>::T>::value,
                                    types::ndarray<bool, types::numpy_expr_to_ndarray<E>::N>
                                   >::type
            isreal(E const& expr)
            {
                types::ndarray<bool, types::numpy_expr_to_ndarray<E>::N> out(expr.shape, __builtin__::None);
                _isreal(expr.begin(), expr.end(), out.begin(), utils::int_<types::numpy_expr_to_ndarray<E>::N>());
                return out;
            }

        template<class E>
            typename std::enable_if<not types::is_complex<typename types::numpy_expr_to_ndarray<E>::T>::value,
                                    types::ndarray<bool, types::numpy_expr_to_ndarray<E>::N>
                                   >::type
            isreal(E const& expr)
            {
                return types::ndarray<bool, types::numpy_expr_to_ndarray<E>::N>(expr.shape, true);
            }
        PROXY(pythonic::numpy, isreal);

    }

}

#endif

