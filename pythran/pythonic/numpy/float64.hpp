#ifndef PYTHONIC_NUMPY_FLOAT64_HPP
#define PYTHONIC_NUMPY_FLOAT64_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace numpy {
        double float64() {return double();}
        PROXY(pythonic::numpy, float64);

    }

}

#endif

