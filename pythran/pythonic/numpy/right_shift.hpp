#ifndef PYTHONIC_NUMPY_RIGHTSHIFT_HPP
#define PYTHONIC_NUMPY_RIGHTSHIFT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/rshift.hpp"

namespace pythonic {

    namespace numpy {
        FPROXY(pythonic::operator_, right_shift, rshift)
    }

}

#endif

