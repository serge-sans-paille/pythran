#ifndef PYTHONIC_NUMPY_ALEN_HPP
#define PYTHONIC_NUMPY_ALEN_HPP

#include "pythonic/include/numpy/alen.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T>
            long alen(T&& expr)
            {
                return expr.shape()[0];
            }

        PROXY_IMPL(pythonic::numpy, alen);

    }

}

#endif
