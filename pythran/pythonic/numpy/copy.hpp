#ifndef PYTHONIC_NUMPY_COPY_HPP
#define PYTHONIC_NUMPY_COPY_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {

        template<class E, class I0, class I1>
            void _copy(I0 ibegin, I0 iend, I1 obegin, utils::int_<1>)
            {
                for(;ibegin != iend; ++ibegin, ++obegin)
                    *obegin = *ibegin;
            }

        template<class E, class I0, class I1, size_t N>
            void _copy(I0 ibegin, I0 iend, I1 obegin, utils::int_<N>)
            {
                for(;ibegin != iend; ++ibegin, ++obegin)
                    _copy((*ibegin).begin(), (*ibegin).end(),
                          (*obegin).begin(), utils::int_<N - 1>());
            }

        template<class E>
            typename std::enable_if<!types::is_array<E>::value,
                                    typename types::numpy_expr_to_ndarray<E>::type
                                    >::type
            copy(E const& v)
            {
                typename types::numpy_expr_to_ndarray<E>::type out(v, __builtin__::None);
                _copy(v.begin(), v.end(), out.begin(),
                      utils::int_<types::numpy_expr_to_ndarray<E>::N>());
                return out;
            }


        // No copy is requiered for numpy_expr
        template<class E>
            auto copy(E && v) -> typename std::enable_if<types::is_array<E>::value, decltype(std::forward<E>(v))>::type
            {
                return std::forward<E>(v);
            }

        template<class T, size_t N>
            types::ndarray<T,N> copy(types::ndarray<T,N> const& a) {
                return a.copy();
            }
        PROXY(pythonic::numpy, copy);
    }
}

#endif

