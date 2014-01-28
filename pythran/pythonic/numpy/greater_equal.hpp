#ifndef PYTHONIC_NUMPY_GREATEREQUAL_HPP
#define PYTHONIC_NUMPY_GREATEREQUAL_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/ge.hpp"

namespace pythonic {

    namespace numpy {
        FPROXY(pythonic::operator_, greater_equal, ge)

    }

}

#endif

