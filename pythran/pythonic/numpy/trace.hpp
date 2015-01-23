#ifndef PYTHONIC_NUMPY_TRACE_HPP
#define PYTHONIC_NUMPY_TRACE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/numexpr_to_ndarray.hpp"

namespace pythonic {

    namespace numpy {

        template<class T>
            typename types::numpy_expr_to_ndarray<T>::T trace(T const& expr, int offset=0)
            {
                static_assert(types::numpy_expr_to_ndarray<T>::N == 2,
                              "Not Implemented : Trace for dimension != 2");

                typename types::numpy_expr_to_ndarray<T>::T res = 0;
                long y_offset = std::max(-offset, 0);
                long x_offset = std::max(0, offset);
                long size = std::min(expr.flat_size() - y_offset,
                                     expr.fast(0).flat_size() - x_offset);
                if(offset < 0)
                    for(long i=0; i<size; i++)
                        res += expr.fast(i + offset).fast(i);
                else if(offset > 0)
                    for(long i=0; i<size; i++)
                        res += expr.fast(i).fast(i + offset);
                else
                    for(long i=0; i<size; i++)
                        res += expr.fast(i).fast(i);
                return res;
            }

        PROXY(pythonic::numpy, trace)

    }

}

#endif

