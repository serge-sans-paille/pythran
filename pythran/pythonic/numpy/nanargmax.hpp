#ifndef PYTHONIC_NUMPY_NANARGMAX_HPP
#define PYTHONIC_NUMPY_NANARGMAX_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/ValueError.hpp"

#include <nt2/include/functions/is_nan.hpp>

namespace pythonic {

    namespace numpy {
        template<class E, class F>
            void _nanargmax(E begin, E end, F& max, long& index, long& where,utils::int_<1>)
            {
                for(; begin != end; ++begin, ++index)
                {
                    auto curr = *begin;
                    if(not nt2::is_nan(curr) and curr > max) {
                        max = curr;
                        where = index;
                    }
                }
            }
        template<class E, class F, size_t N>
            void _nanargmax(E begin, E end, F& max, long& index, long& where, utils::int_<N>)
            {
                for(; begin != end; ++begin)
                    _nanargmax((*begin).begin(), (*begin).end(), max, index, where, utils::int_<N - 1>());
            }
            
        template<class E>
            typename types::numpy_expr_to_ndarray<E>::T
            nanargmax(E const& expr) {
                typename types::numpy_expr_to_ndarray<E>::T max = - std::numeric_limits<typename types::numpy_expr_to_ndarray<E>::T>::infinity();
                long where = -1;
                long index = 0;
                _nanargmax(expr.begin(), expr.end(), max, index, where, utils::int_<types::numpy_expr_to_ndarray<E>::N>());
                if(where >= 0)
                    return where;
                else
                    throw types::ValueError("empty sequence");
            }

        PROXY(pythonic::numpy, nanargmax);

    }

}

#endif

