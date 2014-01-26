#ifndef PYTHONIC_NDARRAY_TOSTRING_HPP
#define PYTHONIC_NDARRAY_TOSTRING_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __ndarray__ {
        template<class T, size_t N>
            types::str tostring(types::ndarray<T,N> const& expr)
            {
                return types::str(reinterpret_cast<const char*>(expr.buffer), expr.size() * sizeof(T));
            }
        NUMPY_EXPR_TO_NDARRAY0(tostring);
        PROXY(pythonic::__ndarray__, tostring);

    }

}

#endif

