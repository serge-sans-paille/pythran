#ifndef PYTHONIC_NUMPY_UNWRAP_HPP
#define PYTHONIC_NUMPY_UNWRAP_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/int_.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/pi.hpp"

#include <nt2/include/functions/max.hpp>

namespace pythonic {

    namespace numpy {
        template<class I0, class I1>
            void _unwrap(I0 ibegin, I0 iend, I1 obegin, double discont, utils::int_<1>)
            {
                *obegin = *ibegin;
                ++ibegin;
                for(; ibegin != iend; ++ibegin, ++obegin)
                {
                    if(nt2::abs(*obegin - *ibegin) > discont)
                        *(obegin + 1) = *ibegin + 2 * pi * int((*obegin - *ibegin) / (discont));
                    else
                        *(obegin + 1) = *ibegin;
                }
            }

        template<class I0, class I1, size_t N>
            void _unwrap(I0 ibegin, I0 iend, I1 obegin, double discont, utils::int_<N>)
            {
                for(; ibegin != iend; ++ibegin, ++obegin)
                    _unwrap((*ibegin).begin(), (*ibegin).end(), (*obegin).begin(), discont, utils::int_<N - 1>());
            }

        template<class E>
            types::ndarray<double, types::numpy_expr_to_ndarray<E>::N> unwrap(E const& expr, double discont = pi)
            {
                discont = nt2::max(discont, pi);
                types::ndarray<double, types::numpy_expr_to_ndarray<E>::N> out(expr.shape(), __builtin__::None);
                _unwrap(expr.begin(), expr.end(), out.begin(), discont, utils::int_<types::numpy_expr_to_ndarray<E>::N>());
                return out;
            }

        PROXY(pythonic::numpy, unwrap)
    }
}

#endif
