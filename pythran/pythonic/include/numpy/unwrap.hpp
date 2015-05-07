#ifndef PYTHONIC_INCLUDE_NUMPY_UNWRAP_HPP
#define PYTHONIC_INCLUDE_NUMPY_UNWRAP_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/int_.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/pi.hpp"

#include <nt2/include/functions/max.hpp>

namespace pythonic {

    namespace numpy {
        template<class I0, class I1>
            void _unwrap(I0 ibegin, I0 iend, I1 obegin, double discont, utils::int_<1>);

        template<class I0, class I1, size_t N>
            void _unwrap(I0 ibegin, I0 iend, I1 obegin, double discont, utils::int_<N>);

        template<class E>
            types::ndarray<double, types::numpy_expr_to_ndarray<E>::N> unwrap(E const& expr, double discont = pi);

        PROXY_DECL(pythonic::numpy, unwrap)
    }
}

#endif
