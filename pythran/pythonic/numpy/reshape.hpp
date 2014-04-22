#ifndef PYTHONIC_NUMPY_RESHAPE_HPP
#define PYTHONIC_NUMPY_RESHAPE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N, size_t M>
            types::ndarray<T, M> reshape( types::ndarray<T,N> const& expr, types::array<long, M> const& s) {
                return expr.reshape(s);
            }

        NUMPY_EXPR_TO_NDARRAY0(reshape);

        PROXY(pythonic::numpy, reshape);

    }

}

#endif

