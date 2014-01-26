#ifndef PYTHONIC_NUMPY_NEGATIVE_HPP
#define PYTHONIC_NUMPY_NEGATIVE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/neg.hpp"

namespace pythonic {

    namespace numpy {
        FPROXY(pythonic::operator_, negative, neg)

    }

}

#endif

