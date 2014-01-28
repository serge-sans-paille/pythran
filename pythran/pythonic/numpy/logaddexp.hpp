#ifndef PYTHONIC_NUMPY_LOGADDEXP_HPP
#define PYTHONIC_NUMPY_LOGADDEXP_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/exp.hpp>

namespace pythonic {

    namespace numpy {
        template<class T0, class T1>
            auto logaddexp(T0 const& t0, T1 const& t1) -> decltype(nt2::log(nt2::exp(t0) + nt2::exp(t1))) {
                return nt2::log(nt2::exp(t0) + nt2::exp(t1));
            }

        namespace wrapper {
            PROXY(pythonic::numpy, logaddexp)
        }
#define NUMPY_BINARY_FUNC_NAME logaddexp
#define NUMPY_BINARY_FUNC_SYM wrapper::proxy::logaddexp
#include "pythonic/types/numpy_binary_expr.hpp"
        PROXY(pythonic::numpy, logaddexp)

    }

}

#endif

