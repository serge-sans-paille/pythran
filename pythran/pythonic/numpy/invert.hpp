#ifndef PYTHONIC_NUMPY_INVERT_HPP
#define PYTHONIC_NUMPY_INVERT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/invert.hpp"

namespace pythonic {

    namespace numpy {
        FPROXY(pythonic::operator_, invert, invert)

    }

}

#endif

