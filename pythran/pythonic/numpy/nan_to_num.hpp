#ifndef PYTHONIC_NUMPY_NANTONUM_HPP
#define PYTHONIC_NUMPY_NANTONUM_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

#include <limits>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_positive.hpp>
#include <nt2/include/functions/is_negative.hpp>

namespace pythonic {

    namespace numpy {
        //TODO could be a unary_expr
        template<class I, class J>
            void _nan_to_num(I begin, I end, J obegin, utils::int_<1>)
            {
                for(; begin != end; ++begin, ++obegin)
                {
                    auto curr = *begin;
                    if(nt2::is_inf(curr)) {
                        if(nt2::is_positive(curr))
                            *obegin = std::numeric_limits<typename std::iterator_traits<J>::value_type>::max();
                        else
                            *obegin = std::numeric_limits<typename std::iterator_traits<J>::value_type>::lowest();
                    }
                    else if(nt2::is_nan(curr))
                        *obegin = 0;
                    else
                        *obegin = curr;
                }
            }
        template<class I, class J, size_t N>
            void _nan_to_num(I begin, I end, J obegin, utils::int_<N>)
            {
                for(; begin != end; ++begin, ++obegin)
                    _nan_to_num((*begin).begin(), (*begin).end(), (*obegin).begin(), utils::int_<N - 1>());
            }

        template<class E>
            typename types::numpy_expr_to_ndarray<E>::type
            nan_to_num(E const& expr) {
                typename types::numpy_expr_to_ndarray<E>::type out(expr.shape, __builtin__::None);
                _nan_to_num(expr.begin(), expr.end(), out.begin(), utils::int_<types::numpy_expr_to_ndarray<E>::N>());
                return out;
            }

        PROXY(pythonic::numpy, nan_to_num);

    }

}

#endif

