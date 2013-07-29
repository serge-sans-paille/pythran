#ifndef PYTHONIC_NUMPY_EQUAL_HPP
#define PYTHONIC_NUMPY_EQUAL_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/eq.hpp"

namespace pythonic {

    namespace numpy {

        FPROXY(pythonic::operator_, equal, eq)

    }

}

#endif

