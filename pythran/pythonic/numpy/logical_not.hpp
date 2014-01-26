#ifndef PYTHONIC_NUMPY_LOGICALNOT_HPP
#define PYTHONIC_NUMPY_LOGICALNOT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/not_.hpp"

namespace pythonic {

    namespace numpy {
        FPROXY(pythonic::operator_, logical_not, not_)
    }

}

#endif

