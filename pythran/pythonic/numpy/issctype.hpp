#ifndef PYTHONIC_NUMPY_ISSCTYPE_HPP
#define PYTHONIC_NUMPY_ISSCTYPE_HPP

#include "pythonic/include/numpy/issctype.hpp"

#include "pythonic/numpy/isscalar.hpp"
#include "pythonic/types/numpy_type.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            constexpr bool issctype(E const& expr)
            {
                return not isscalar(expr) and isscalar(typename types::numpy_type<E>::type()); 
            }

        PROXY_IMPL(pythonic::numpy, issctype);

    }

}

#endif
