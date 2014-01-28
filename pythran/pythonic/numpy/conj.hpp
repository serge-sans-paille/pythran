#ifndef PYTHONIC_NUMPY_CONJ_HPP
#define PYTHONIC_NUMPY_CONJ_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/conj.hpp>

namespace pythonic {

    namespace numpy {
        using nt2::conj;

        namespace wrapper {
            PROXY(pythonic::numpy, conj)

        }
#define NUMPY_UNARY_FUNC_NAME conj
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::conj
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, conj)

    }

}

#endif

