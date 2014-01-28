#ifndef PYTHONIC_NUMPY_GREATER_HPP
#define PYTHONIC_NUMPY_GREATER_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/gt.hpp"

namespace pythonic {

    namespace numpy {

        FPROXY(pythonic::operator_, greater, gt)

    }

}

#endif

