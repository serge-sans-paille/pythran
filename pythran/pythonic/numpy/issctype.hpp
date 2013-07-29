#ifndef PYTHONIC_NUMPY_ISSCTYPE_HPP
#define PYTHONIC_NUMPY_ISSCTYPE_HPP

#include "pythonic/numpy/isscalar.hpp"
#include "pythonic/types/numpy_type.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            constexpr bool issctype(E const& expr) {
                return isscalar(typename types::numpy_type<E>::type()); 
            }
        PROXY(pythonic::numpy, issctype);

    }

}

#endif

