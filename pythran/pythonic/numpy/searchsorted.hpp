#ifndef PYTHONIC_NUMPY_SEARCHSORTED_HPP
#define PYTHONIC_NUMPY_SEARCHSORTED_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/utils/int_.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/__builtin__/None.hpp"
#include "pythonic/__builtin__/ValueError.hpp"
#include "pythonic/numpy/asarray.hpp"

#include <algorithm>

namespace pythonic {

    namespace numpy {

        template<class T, class U>
            typename std::enable_if<!types::is_numexpr_arg<T>::value, long>::type
            searchsorted(U const& a, T const& v, types::str const &side = "left")
            {
                if(side[0]=='l')
                {
                    return std::lower_bound(a.begin(), a.end(), v) - a.begin();
                }
                else if(side[0]=='r')
                {
                    return std::upper_bound(a.begin(), a.end(), v) - a.begin();
                }
                else
                    throw types::ValueError("'" + side + "' is an invalid value for keyword 'side'");
            }
        template<class E, class I0, class I1>
            void _search_sorted(E const& a, I0 ibegin, I0 iend, I1 obegin, types::str const &side, utils::int_<1>)
            {
                for(;ibegin != iend; ++ibegin, ++obegin)
                    *obegin = searchsorted(a, *ibegin, side);
            }

        template<class E, class I0, class I1, size_t N>
            void _search_sorted(E const& a, I0 ibegin, I0 iend, I1 obegin, types::str const &side, utils::int_<N>)
            {
                for(;ibegin != iend; ++ibegin, ++obegin)
                    _search_sorted(a, (*ibegin).begin(), (*ibegin).end(),
                                   (*obegin).begin(), side, utils::int_<N - 1>());
            }

        template<class E, class T>
            typename std::enable_if<types::is_numexpr_arg<E>::value,
                                    types::ndarray<long, types::numpy_expr_to_ndarray<E>::N>>::type
            searchsorted(T const& a, E const& v, types::str const & side = "left")
            {
                static_assert(types::numpy_expr_to_ndarray<T>::N == 1,
                              "Not Implemented : searchsorted for dimension != 1");

                types::ndarray<long, types::numpy_expr_to_ndarray<E>::N> out(asarray(v).shape(), __builtin__::None);
                _search_sorted(a, v.begin(), v.end(), out.begin(), side,
                               utils::int_<types::numpy_expr_to_ndarray<E>::N>());
                return out;
            }

            PROXY(pythonic::numpy, searchsorted);

    }

}

#endif

