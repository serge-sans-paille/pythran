#ifndef PYTHONIC_NUMPY_FMOD_HPP
#define PYTHONIC_NUMPY_FMOD_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/mod.hpp>

namespace pythonic {

    namespace numpy {
        ALIAS(fmod, nt2::mod)

            namespace wrapper {
                PROXY(pythonic::numpy, fmod)
            }
#define NUMPY_BINARY_FUNC_NAME fmod
#define NUMPY_BINARY_FUNC_SYM wrapper::proxy::fmod
#include "pythonic/types/numpy_binary_expr.hpp"
        PROXY(pythonic::numpy, fmod)

    }

}

#endif

