#ifndef PYTHONIC_INCLUDE_NUMPY_DIFF_HPP
#define PYTHONIC_INCLUDE_NUMPY_DIFF_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/asarray.hpp"

namespace pythonic {

    namespace numpy {

        template<class E>
            typename types::numpy_expr_to_ndarray<E>::type
            diff(E const& expr, long n=1);

        PROXY_DECL(pythonic::numpy, diff);

    }

}

#endif
