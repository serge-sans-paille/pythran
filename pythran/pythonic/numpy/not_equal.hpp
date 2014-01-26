#ifndef PYTHONIC_NUMPY_NOTEQUAL_HPP
#define PYTHONIC_NUMPY_NOTEQUAL_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/ne.hpp"

namespace pythonic {

    namespace numpy {
        FPROXY(pythonic::operator_, not_equal, ne)

    }

}

#endif

