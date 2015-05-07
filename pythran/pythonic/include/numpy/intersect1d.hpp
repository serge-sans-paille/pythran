#ifndef PYTHONIC_INCLUDE_NUMPY_INTERSECT1D_HPP
#define PYTHONIC_INCLUDE_NUMPY_INTERSECT1D_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/combined.hpp"
#include "pythonic/numpy/asarray.hpp"

#include <algorithm>

namespace pythonic {

    namespace numpy {
        template<class E, class F>
            types::ndarray<typename __combined<typename types::numpy_expr_to_ndarray<E>::T,
                                               typename types::numpy_expr_to_ndarray<F>::T
                                              >::type,
                           1>
            intersect1d(E const& e, F const& f);

        PROXY_DECL(pythonic::numpy, intersect1d);

    }

}

#endif
