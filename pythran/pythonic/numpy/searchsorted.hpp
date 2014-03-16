#ifndef PYTHONIC_NUMPY_SEARCHSORTED_HPP
#define PYTHONIC_NUMPY_SEARCHSORTED_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/__builtin__/None.hpp"
#include "pythonic/__builtin__/ValueError.hpp"
#include "pythonic/numpy/asarray.hpp"

#include <algorithm>

namespace pythonic {

    namespace numpy {
        template<class E, class T>
            typename std::enable_if<types::is_numexpr_arg<E>::value, types::ndarray<long, types::numpy_expr_to_ndarray<E>::N>>::type searchsorted(types::ndarray<T,1> const& a, E const& v, types::str const & side = "left")
            {
                types::ndarray<T,types::numpy_expr_to_ndarray<E>::N> to_search = asarray(v);
                types::ndarray<long, types::numpy_expr_to_ndarray<E>::N> out(to_search.shape, __builtin__::None);
                if(side[0]=='l')
                {
                    auto itosearch = to_search.fbegin();
                    for(auto iout = out.fbegin(), end = out.fend(); iout != end; ++iout, ++itosearch)
                        *iout = std::lower_bound(a.fbegin(), a.fend(), *itosearch) - a.fbegin();
                }
                else if(side[0]=='r')
                {
                    auto itosearch = to_search.fbegin();
                    for(auto iout = out.fbegin(), end = out.fend(); iout != end; ++iout, ++itosearch)
                        *iout = std::upper_bound(a.fbegin(), a.fend(), *itosearch) - a.fbegin();
                }
                else
                    throw types::ValueError("'" + side + "' is an invalid value for keyword 'side'");
                return out;
            }

        template<class T>
            long searchsorted(types::ndarray<T,1> const& a, T const& v, types::str const &side = "left")
            {
                if(side[0]=='l')
                {
                    return std::lower_bound(a.fbegin(), a.fend(), v) - a.buffer;
                }
                else if(side[0]=='r')
                {
                    return std::upper_bound(a.fbegin(), a.fend(), v) - a.buffer;
                }
                else
                    throw types::ValueError("'" + side + "' is an invalid value for keyword 'side'");
            }

        NUMPY_EXPR_TO_NDARRAY0(searchsorted)
            PROXY(pythonic::numpy, searchsorted);

    }

}

#endif

