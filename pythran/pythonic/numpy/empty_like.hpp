#ifndef PYTHONIC_NUMPY_EMPTYLIKE_HPP
#define PYTHONIC_NUMPY_EMPTYLIKE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/empty.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            auto empty_like(E const&expr)
            -> decltype(empty(expr.shape))
            {
                return empty(expr.shape);
            }
        PROXY(pythonic::numpy, empty_like)
    }

}

#endif

