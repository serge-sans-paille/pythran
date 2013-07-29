#ifndef PYTHONIC_NUMPY_TRACE_HPP
#define PYTHONIC_NUMPY_TRACE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T>
            T trace(types::ndarray<T,2> const& expr, int offset=0)
            {
                T res = 0;
                long size = std::min(expr.shape[0] + std::min(offset, 0), expr.shape[1] - std::max(0, offset));
                for(int i=0; i<size; ++i)
                    res += expr.buffer[i * expr.shape[1] + i + offset];
                return res;
            }
        NUMPY_EXPR_TO_NDARRAY0(trace)
            PROXY(pythonic::numpy, trace)

    }

}

#endif

