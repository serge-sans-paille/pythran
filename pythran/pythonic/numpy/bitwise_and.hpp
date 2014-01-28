#ifndef PYTHONIC_NUMPY_BITWISE_AND_HPP
#define PYTHONIC_NUMPY_BITWISE_AND_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/and_.hpp"

namespace pythonic {

    namespace numpy {
        FPROXY(pythonic::operator_, bitwise_and, and_)
    }
}

#endif

