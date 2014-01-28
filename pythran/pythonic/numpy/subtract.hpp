#ifndef PYTHONIC_NUMPY_SUBTRACT_HPP
#define PYTHONIC_NUMPY_SUBTRACT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/sub.hpp"

namespace pythonic {

    namespace numpy {
        FPROXY(pythonic::operator_, subtract, sub)

    }

}

#endif

