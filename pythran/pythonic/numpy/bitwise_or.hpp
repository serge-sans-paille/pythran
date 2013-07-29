#ifndef PYTHONIC_NUMPY_BITWISE_OR_HPP
#define PYTHONIC_NUMPY_BITWISE_OR_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/or_.hpp"

namespace pythonic {

    namespace numpy {
        FPROXY(pythonic::operator_, bitwise_or, or_)
    }
}

#endif

