#ifndef PYTHONIC_NUMPY_NANARGMIN_HPP
#define PYTHONIC_NUMPY_NANARGMIN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/is_nan.hpp>
#include "pythonic/__builtin__/ValueError.hpp"

namespace pythonic {

    namespace numpy {
        template<class E, class F>
            void _nanargmin(E begin, E end, F& min, long& index, long& where,utils::int_<1>)
            {
                for(; begin != end; ++begin, ++index)
                {
                    auto curr = *begin;
                    if(not nt2::is_nan(curr) and curr < min) {
                        min = curr;
                        where = index;
                    }
                }
            }
        template<class E, class F, size_t N>
            void _nanargmin(E begin, E end, F& min, long& index, long& where, utils::int_<N>)
            {
                for(; begin != end; ++begin)
                    _nanargmin((*begin).begin(), (*begin).end(), min, index, where, utils::int_<N - 1>());
            }
            
        template<class E>
            typename types::numpy_expr_to_ndarray<E>::T
            nanargmin(E const& expr) {
                typename types::numpy_expr_to_ndarray<E>::T min = std::numeric_limits<typename types::numpy_expr_to_ndarray<E>::T>::infinity();
                long where = -1;
                long index = 0;
                _nanargmin(expr.begin(), expr.end(), min, index, where, utils::int_<types::numpy_expr_to_ndarray<E>::N>());
                if(where >= 0)
                    return where;
                else
                    throw types::ValueError("empty sequence");
            }
        PROXY(pythonic::numpy, nanargmin);

    }

}

#endif

