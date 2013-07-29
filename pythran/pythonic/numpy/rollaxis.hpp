#ifndef PYTHONIC_NUMPY_ROLLAXIS_HPP
#define PYTHONIC_NUMPY_ROLLAXIS_HPP

#include "pythonic/numpy/transpose.hpp"
#include "pythonic/numpy/copy.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N>
            types::ndarray<T,N> rollaxis(types::ndarray<T,N> const & a, int axis, int start=0)
            {
                if(start>=axis)
                    return copy(a);
                long t[N];
                for(unsigned long i = 0; i<start; ++i)
                    t[i] = i;
                t[start] = axis;
                for(unsigned long i = start + 1; i<=axis; ++i)
                    t[i] = i-1;
                for(unsigned long i = axis + 1; i<N; ++i)
                    t[i] = i;
                return _transpose(a, t);
            }

        NUMPY_EXPR_TO_NDARRAY0(rollaxis);
        PROXY(pythonic::numpy, rollaxis);

    }

}

#endif

