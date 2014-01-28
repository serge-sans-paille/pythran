#ifndef PYTHONIC_NUMPY_LESSEQUAL_HPP
#define PYTHONIC_NUMPY_LESSEQUAL_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/le.hpp"

namespace pythonic {

    namespace numpy {
        FPROXY(pythonic::operator_, less_equal, le)

    }

}

#endif

