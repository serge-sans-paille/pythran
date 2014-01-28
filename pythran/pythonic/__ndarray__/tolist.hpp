#ifndef PYTHONIC_NDARRAY_TOLIST_HPP
#define PYTHONIC_NDARRAY_TOLIST_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace __ndarray__ {
        template<class T, size_t N>
            struct tolist_type
            {
                typedef types::list<typename tolist_type<T, N-1>::type> type;
            };

        template<class T>
            struct tolist_type<T, 1>
            {
                typedef types::list<T> type;
            };

        template<class T>
            types::list<T> tolist(types::ndarray<T,1> const& expr)
            {
                return types::list<T>(expr.buffer, expr.buffer + expr.size());
            }

        template<class T, size_t N>
            typename tolist_type<T, N>::type tolist(types::ndarray<T,N> const& expr)
            {
                typename tolist_type<T, N>::type out(0);
                for(types::ndarray<T,N-1> const& elts: expr)
                    out.push_back(tolist(elts));
                return out;
            }
        NUMPY_EXPR_TO_NDARRAY0(tolist);
        PROXY(pythonic::__ndarray__, tolist);

    }

}

#endif

