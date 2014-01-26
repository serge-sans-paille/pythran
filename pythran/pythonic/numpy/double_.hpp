#ifndef PYTHONIC_NUMPY_DOUBLE_HPP
#define PYTHONIC_NUMPY_DOUBLE_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace numpy {
        double double_() {return double();}
        PROXY(pythonic::numpy, double_);

    }

}

#endif

