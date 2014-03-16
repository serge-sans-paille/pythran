#ifndef PYTHONIC_NUMPY_NANSUM_HPP
#define PYTHONIC_NUMPY_NANSUM_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_type.hpp"

#include <nt2/include/functions/is_nan.hpp>

namespace pythonic {

    namespace numpy {
        template<class E, class F>
            void _nansum(E begin, E end, F& sum, utils::int_<1>)
            {
                for(; begin != end; ++begin)
                {
                    auto curr = *begin;
                    if(not nt2::is_nan(curr))
                        sum += curr;
                }
            }
        template<class E, class F, size_t N>
            void _nansum(E begin, E end, F& sum, utils::int_<N>)
            {
                for(; begin != end; ++begin)
                    _nansum((*begin).begin(), (*begin).end(), sum, utils::int_<N - 1>());
            }
            
        template<class E>
            typename types::numpy_expr_to_ndarray<E>::T
            nansum(E const& expr) {
                typename types::numpy_expr_to_ndarray<E>::T s = 0;
                _nansum(expr.begin(), expr.end(), s, utils::int_<types::numpy_expr_to_ndarray<E>::N>());
                return s;
            }

        PROXY(pythonic::numpy, nansum);

    }

}

#endif

