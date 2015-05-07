#ifndef PYTHONIC_INCLUDE_NUMPY_ISSCTYPE_HPP
#define PYTHONIC_INCLUDE_NUMPY_ISSCTYPE_HPP

#include "pythonic/numpy/isscalar.hpp"
#include "pythonic/types/numpy_type.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            constexpr bool issctype(E const& expr);

        PROXY_DECL(pythonic::numpy, issctype);

    }

}

#endif
