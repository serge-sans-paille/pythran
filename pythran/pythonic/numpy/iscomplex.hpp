#ifndef PYTHONIC_NUMPY_ISCOMPLEX_HPP
#define PYTHONIC_NUMPY_ISCOMPLEX_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/traits.hpp"

namespace pythonic {

    namespace numpy {

        //TODO this could be a unary_expr
        template<class I, class O>
            void _iscomplex(I begin, I end, O obegin, utils::int_<1>)
            {
                for(; begin != end; ++begin, ++obegin)
                    *obegin = (*begin).imag() != 0.;
            }
        template<class I, class O, size_t N>
            void _iscomplex(I begin, I end, O obegin, utils::int_<N>)
            {
                for(; begin != end; ++begin, ++obegin)
                    _iscomplex((*begin).begin(), (*begin).end(), (*obegin).begin(), utils::int_<N-1>());
            }

        template<class E>
            typename std::enable_if<types::is_complex<typename types::numpy_expr_to_ndarray<E>::T>::value,
                                    types::ndarray<bool, types::numpy_expr_to_ndarray<E>::N>
                                   >::type
            iscomplex(E const& expr)
            {
                types::ndarray<bool, types::numpy_expr_to_ndarray<E>::N> out(expr.shape, __builtin__::None);
                _iscomplex(expr.begin(), expr.end(), out.begin(), utils::int_<types::numpy_expr_to_ndarray<E>::N>());
                return out;
            }

        template<class E>
            typename std::enable_if<not types::is_complex<typename types::numpy_expr_to_ndarray<E>::T>::value,
                                    types::ndarray<bool, types::numpy_expr_to_ndarray<E>::N>
                                   >::type
            iscomplex(E const& expr)
            {
                return types::ndarray<bool, types::numpy_expr_to_ndarray<E>::N>(expr.shape, false);
            }

        PROXY(pythonic::numpy, iscomplex);

    }

}

#endif

