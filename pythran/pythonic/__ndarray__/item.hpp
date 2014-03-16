#ifndef PYTHONIC_NDARRAY_ITEM_HPP
#define PYTHONIC_NDARRAY_ITEM_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace __ndarray__ {

        template<class T, size_t N>
            T item(types::ndarray<T, N> const& expr, long i)
            {
                if(i<0) i += expr.size();
                return *(expr.fbegin() + i);
            }
        template<class E, size_t N>
            auto item(E&& expr, types::array<long, N> const& i) -> decltype(expr[i])
            {
                return expr[i];
            }
        PROXY(pythonic::__ndarray__, item);

    }

}

#endif

