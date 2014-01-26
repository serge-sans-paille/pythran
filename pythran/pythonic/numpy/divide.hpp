#ifndef PYTHONIC_NUMPY_DIVIDE_HPP
#define PYTHONIC_NUMPY_DIVIDE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/div.hpp"

namespace pythonic {

    namespace numpy {
        FPROXY(pythonic::operator_, divide, div)

    }

}

#endif

