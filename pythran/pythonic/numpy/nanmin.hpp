#ifndef PYTHONIC_NUMPY_NANMIN_HPP
#define PYTHONIC_NUMPY_NANMIN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/ValueError.hpp"

#include <nt2/include/functions/is_nan.hpp>

namespace pythonic {

    namespace numpy {
        template<class E, class F>
            void _nanmin(E begin, E end, F& min, utils::int_<1>)
            {
                for(; begin != end; ++begin)
                {
                    auto curr = *begin;
                    if(not nt2::is_nan(curr) and curr < min)
                        min = curr;
                }
            }
        template<class E, class F, size_t N>
            void _nanmin(E begin, E end, F& min, utils::int_<N>)
            {
                for(; begin != end; ++begin)
                    _nanmin((*begin).begin(), (*begin).end(), min, utils::int_<N - 1>());
            }
            
        template<class E>
            typename types::numpy_expr_to_ndarray<E>::T
            nanmin(E const& expr) {
                typename types::numpy_expr_to_ndarray<E>::T min = std::numeric_limits<typename types::numpy_expr_to_ndarray<E>::T>::max();
                _nanmin(expr.begin(), expr.end(), min, utils::int_<types::numpy_expr_to_ndarray<E>::N>());
                return min;
            }

        PROXY(pythonic::numpy, nanmin);

    }

}

#endif

