#ifndef PYTHONIC_NUMPY_LEFT_SHIFT_HPP
#define PYTHONIC_NUMPY_LEFT_SHIFT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/lshift.hpp"

namespace pythonic {

    namespace numpy {

        FPROXY(pythonic::operator_, left_shift, lshift)

    }

}

#endif

