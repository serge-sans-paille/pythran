#ifndef PYTHONIC_INCLUDE_NUMPY_ISREALOBJ_HPP
#define PYTHONIC_INCLUDE_NUMPY_ISREALOBJ_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/traits.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            constexpr bool isrealobj(E const& expr);

        PROXY_DECL(pythonic::numpy, isrealobj);

    }

}

#endif
