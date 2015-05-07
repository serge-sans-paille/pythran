#ifndef PYTHONIC_INCLUDE_NUMPY_ASSCALAR_HPP
#define PYTHONIC_INCLUDE_NUMPY_ASSCALAR_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/asarray.hpp"
#include "pythonic/__builtin__/ValueError.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            typename E::dtype asscalar(E const& expr);

        PROXY_DECL(pythonic::numpy, asscalar);

    }

}

#endif
