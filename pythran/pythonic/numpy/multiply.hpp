#ifndef PYTHONIC_NUMPY_MULTIPLY_HPP
#define PYTHONIC_NUMPY_MULTIPLY_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/mul.hpp"

namespace pythonic {

    namespace numpy {
        FPROXY(pythonic::operator_, multiply, mul)

    }

}

#endif

