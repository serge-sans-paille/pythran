#ifndef PYTHONIC_NUMPY_ISCLOSE_HPP
#define PYTHONIC_NUMPY_ISCLOSE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/abs.hpp"
#include "pythonic/numpy/isfinite.hpp"
#include "pythonic/numpy/isnan.hpp"

namespace pythonic {
    namespace numpy {

        namespace wrapper {
            template<class T0, class T1>
                bool isclose(T0 const& u, T1 const& v, double rtol=1e-5, double atol=1e-8, bool equal_nan=false)
                {
                    if (proxy::isfinite()(u) && proxy::isfinite()(v))
                        return proxy::abs()(u-v) <= (atol + rtol * proxy::abs()(v));
                    else if (proxy::isnan()(u) && proxy::isnan()(v))
                        return equal_nan;
                    else
                        return (u == v);
                }
        }
#define NUMPY_NARY_FUNC_NAME isclose
#define NUMPY_NARY_FUNC_SYM wrapper::isclose
#include "pythonic/types/numpy_nary_expr.hpp"

    }
}

#endif

