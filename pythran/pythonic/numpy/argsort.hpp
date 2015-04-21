#ifndef PYTHONIC_NUMPY_ARGSORT_HPP
#define PYTHONIC_NUMPY_ARGSORT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N>
            types::ndarray<long, N> argsort(types::ndarray<T,N> const& a) {
                size_t last_axis = a.shape()[N-1];
                size_t n = a.flat_size();
                types::ndarray<long, N> indices(a.shape(), __builtin__::None);
                for(long j=0, * iter_indices = indices.buffer, *end_indices = indices.buffer + n;
                        iter_indices != end_indices;
                        iter_indices += last_axis, j+=last_axis)
                {
                    // fill with the original indices
                    std::iota(iter_indices, iter_indices + last_axis, 0L);
                    // sort the index using the value from a
                    std::sort(iter_indices, iter_indices + last_axis,
                            [&a,j](long i1, long i2) {return *(a.fbegin() + j + i1) < *(a.fbegin() + j + i2);});
                }
                return indices;
            }

        NUMPY_EXPR_TO_NDARRAY0(argsort);

        PROXY(pythonic::numpy, argsort);

    }

}

#endif

