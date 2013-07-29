#ifndef PYTHONIC_NUMPY_TRUEDIVIDE_HPP
#define PYTHONIC_NUMPY_TRUEDIVIDE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/div.hpp"

namespace pythonic {

    namespace numpy {
        // FIXME: this is not always a true_divide...
        FPROXY(pythonic::operator_, true_divide, div)

    }

}

#endif

