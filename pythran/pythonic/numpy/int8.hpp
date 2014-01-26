#ifndef PYTHONIC_NUMPY_INT8_HPP
#define PYTHONIC_NUMPY_INT8_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace numpy {

        uint8_t int8() {return int8_t();}
        PROXY(pythonic::numpy, int8);

    }

}

#endif

