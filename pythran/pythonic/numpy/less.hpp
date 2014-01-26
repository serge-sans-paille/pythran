#ifndef PYTHONIC_NUMPY_LESS_HPP
#define PYTHONIC_NUMPY_LESS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/lt.hpp"

namespace pythonic {

    namespace numpy {
        FPROXY(pythonic::operator_, less, lt)

    }

}

#endif

