#ifndef PYTHONIC_INCLUDE_NUMPY_ONESLIKE_HPP
#define PYTHONIC_INCLUDE_NUMPY_ONESLIKE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/ones.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            auto ones_like(E const&expr)
            -> decltype(ones(expr.shape()));

        PROXY_DECL(pythonic::numpy, ones_like)

    }

}

#endif
