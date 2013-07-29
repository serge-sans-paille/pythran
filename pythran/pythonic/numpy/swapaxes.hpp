#ifndef PYTHONIC_NUMPY_SWAPAXES_HPP
#define PYTHONIC_NUMPY_SWAPAXES_HPP

#include "pythonic/numpy/transpose.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N>
            types::ndarray<T,N> swapaxes(types::ndarray<T,N> const & a, int axis1, int axis2)
            {
                long t[N];
                for(unsigned long i = 0; i<N; ++i)
                    t[i] = i;
                std::swap(t[axis1], t[axis2]);
                return _transpose(a, t);
            }

        NUMPY_EXPR_TO_NDARRAY0(swapaxes);
        PROXY(pythonic::numpy, swapaxes);

    }

}

#endif

