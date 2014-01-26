#ifndef PYTHONIC_NDARRAY_ITEM_HPP
#define PYTHONIC_NDARRAY_ITEM_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace __ndarray__ {
        template<class E>
            auto item(E&& expr, long i) -> decltype(expr.at(i))
            {
                return expr.at(i);
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

