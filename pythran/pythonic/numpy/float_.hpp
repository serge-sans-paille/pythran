#ifndef PYTHONIC_NUMPY_FLOAT_HPP
#define PYTHONIC_NUMPY_FLOAT_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace numpy {

        float float_() {return float();}
        PROXY(pythonic::numpy, float_);

    }

}

#endif

