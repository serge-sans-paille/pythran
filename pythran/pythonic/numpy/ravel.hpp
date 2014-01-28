#ifndef PYTHONIC_NUMPY_RAVEL_HPP
#define PYTHONIC_NUMPY_RAVEL_HPP

#include "pythonic/numpy/reshape.hpp"
#include "pythonic/utils/numpy_conversion.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N>
            types::ndarray<T,1> ravel(types::ndarray<T,N> const& expr)
            {
                return reshape(expr, (long)expr.size());
            }

        NUMPY_EXPR_TO_NDARRAY0(ravel);
        PROXY(pythonic::numpy, ravel);

    }

}

#endif

