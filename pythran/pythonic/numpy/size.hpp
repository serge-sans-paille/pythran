#ifndef PYTHONIC_NUMPY_SIZE_HPP
#define PYTHONIC_NUMPY_SIZE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {

        template <class E>
            auto size(E const& e) -> decltype(e.size()) {
                return e.size();
            }

        PROXY(pythonic::numpy, size)
    }
}

#endif


