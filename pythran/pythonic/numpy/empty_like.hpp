#ifndef PYTHONIC_NUMPY_EMPTYLIKE_HPP
#define PYTHONIC_NUMPY_EMPTYLIKE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/empty.hpp"

namespace pythonic {

    namespace numpy {
        template<class E, class dtype>
            auto empty_like(E const&expr, dtype d=dtype())
            -> decltype(empty(expr.shape(), d))
            {
                return empty(expr.shape(), d);
            }
        template<class E>
            auto empty_like(E const&expr, types::none_type d=__builtin__::None)
            -> decltype(empty(expr.shape(), typename E::dtype()))
            {
                return empty(expr.shape(), typename E::dtype());
            }
        PROXY(pythonic::numpy, empty_like)
    }

}

#endif

