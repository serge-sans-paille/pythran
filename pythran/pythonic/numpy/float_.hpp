#ifndef PYTHONIC_NUMPY_FLOAT_HPP
#define PYTHONIC_NUMPY_FLOAT_HPP

#include "pythonic/include/numpy/float_.hpp"

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace numpy {

        float float_()
        {
            return float();
        }

        PROXY_IMPL(pythonic::numpy, float_);

    }

}

#endif
