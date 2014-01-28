#ifndef PYTHONIC_NUMPY_IDENTITY_HPP
#define PYTHONIC_NUMPY_IDENTITY_HPP

#include "pythonic/numpy/eye.hpp"

namespace pythonic {

    namespace numpy {
        template<class dtype=double>
            auto identity(long n, dtype d=dtype()) -> decltype(eye(n,n,0,d)) {
                return eye(n,n,0,d);
            }
        PROXY(pythonic::numpy, identity);

    }

}

#endif

