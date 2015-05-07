#ifndef PYTHONIC_NUMPY_SIZE_HPP
#define PYTHONIC_NUMPY_SIZE_HPP

#include "pythonic/include/numpy/size.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {

        template <class E>
            auto size(E const& e) -> decltype(e.flat_size())
            {
                return e.flat_size();
            }

        PROXY_IMPL(pythonic::numpy, size)
    }
}

#endif
