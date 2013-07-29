#ifndef PYTHONIC_NUMPY_LOGADDEXP2_HPP
#define PYTHONIC_NUMPY_LOGADDEXP2_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

#include <nt2/include/functions/log2.hpp>
#include <nt2/include/functions/pow.hpp>
namespace pythonic {

    namespace numpy {
        template<class T0, class T1>
            auto logaddexp2(T0 const& t0, T1 const& t1) -> decltype(nt2::log2(nt2::pow(T0(2),t0) + nt2::pow(T1(2),t1))) {
                return nt2::log2(nt2::pow(T0(2),t0) + nt2::pow(T1(2),t1));
            }
        namespace wrapper {
            PROXY(pythonic::numpy, logaddexp2)
        }
#define NUMPY_BINARY_FUNC_NAME logaddexp2
#define NUMPY_BINARY_FUNC_SYM wrapper::proxy::logaddexp2
#include "pythonic/types/numpy_binary_expr.hpp"
        PROXY(pythonic::numpy, logaddexp2)

    }

}

#endif

