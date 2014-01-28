#ifndef PYTHONIC_NUMPY_RESHAPE_HPP
#define PYTHONIC_NUMPY_RESHAPE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N, class ...S>
            types::ndarray<T, sizeof...(S)> reshape( types::ndarray<T,N> const& expr, S&& ...s) {
                return expr.reshape(types::make_tuple(std::forward<S>(s)...));
            }

        NUMPY_EXPR_TO_NDARRAY0(reshape);

        PROXY(pythonic::numpy, reshape);

    }

}

#endif

