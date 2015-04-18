#ifndef PYTHONIC_NUMPY_SHAPE_HPP
#define PYTHONIC_NUMPY_SHAPE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {

        template <class E>
            auto shape(E const& e) -> decltype(e.shape()) {
                return e.shape();
            }

        PROXY(pythonic::numpy, shape)
    }
}

#endif


