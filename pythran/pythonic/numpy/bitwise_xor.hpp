#ifndef PYTHONIC_NUMPY_BITWISE_XOR_HPP
#define PYTHONIC_NUMPY_BITWISE_XOR_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/__xor__.hpp"

namespace pythonic {

    namespace numpy {
        FPROXY(pythonic::operator_, bitwise_xor, __xor__)
    }
}

#endif

