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
                auto expr_iter = expr.fbegin();
                for(auto out_iter = out.fbegin(), out_end = out.fend(); out_iter != out_end; ++out_iter)
                    *out_iter = *(expr_iter + *out_iter);
                return out;
            }
        NUMPY_EXPR_TO_NDARRAY0(take);
        PROXY(pythonic::numpy, take);

    }

}

#endif

