#ifndef PYTHONIC_INCLUDE_NUMPY_TRACE_HPP
#define PYTHONIC_INCLUDE_NUMPY_TRACE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/numexpr_to_ndarray.hpp"

namespace pythonic {

    namespace numpy {

        template<class T>
            typename types::numpy_expr_to_ndarray<T>::T trace(T const& expr, int offset=0);

        PROXY_DECL(pythonic::numpy, trace)

    }

}

#endif
