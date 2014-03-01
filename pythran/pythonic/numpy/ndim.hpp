#ifndef PYTHONIC_NUMPY_NDIM_HPP
#define PYTHONIC_NUMPY_NDIM_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {

        template <class E>
            auto ndim(E const& e) -> decltype(__builtin__::getattr<types::attr::NDIM>(e)) {
                return __builtin__::getattr<types::attr::NDIM>(e);
            }

        PROXY(pythonic::numpy, ndim)
    }
}

#endif


