#ifndef PYTHONIC_NUMPY_TAKE_HPP
#define PYTHONIC_NUMPY_TAKE_HPP

#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/numpy/asarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class F, class T, size_t N>
            typename types::numpy_expr_to_ndarray<F>::type take(types::ndarray<T,N> const & expr, F const& indices)
            {
                typename types::numpy_expr_to_ndarray<F>::type out = asarray(indices);
                for(size_t i=0; i<out.size(); ++i)
                    out.buffer[i] = expr.at(out.buffer[i]);
                return out;
            }
        NUMPY_EXPR_TO_NDARRAY0(take);
        PROXY(pythonic::numpy, take);

    }

}

#endif

