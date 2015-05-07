#ifndef PYTHONIC_INCLUDE_NUMPY_TRIL_HPP
#define PYTHONIC_INCLUDE_NUMPY_TRIL_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T>
            types::ndarray<T,2> tril(types::ndarray<T,2> const& expr, int k = 0);

        NUMPY_EXPR_TO_NDARRAY0_DECL(tril)
        PROXY_DECL(pythonic::numpy, tril)

    }

}

#endif
