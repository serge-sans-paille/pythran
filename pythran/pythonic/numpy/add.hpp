#ifndef PYTHONIC_NUMPY_ADD_HPP
#define PYTHONIC_NUMPY_ADD_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/add.hpp"

namespace pythonic {

    namespace numpy {

        PROXY(pythonic::operator_, add)
    }

}

#endif

