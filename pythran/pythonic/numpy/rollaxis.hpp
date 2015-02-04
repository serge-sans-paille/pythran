#ifndef PYTHONIC_NUMPY_ROLLAXIS_HPP
#define PYTHONIC_NUMPY_ROLLAXIS_HPP

#include "pythonic/numpy/transpose.hpp"
#include "pythonic/numpy/copy.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N>
            types::ndarray<T,N> rollaxis(types::ndarray<T,N> const & a, long axis, long start=0)
            {
                if(start>=axis)
                    return copy(a);
                long t[N];
                for(long i = 0; i<start; ++i)
                    t[i] = i;
                t[start] = axis;
                for(long i = start + 1; i<=axis; ++i)
                    t[i] = i-1;
                for(long i = axis + 1, n = N; i<n; ++i)
                    t[i] = i;
                return _transpose(a, t);
            }

        NUMPY_EXPR_TO_NDARRAY0(rollaxis);
        PROXY(pythonic::numpy, rollaxis);

    }

}

#endif

