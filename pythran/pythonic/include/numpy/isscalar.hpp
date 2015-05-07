#ifndef PYTHONIC_INCLUDE_NUMPY_ISSCALAR_HPP
#define PYTHONIC_INCLUDE_NUMPY_ISSCALAR_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/traits.hpp"
#include "pythonic/types/str.hpp"

#include <type_traits>

namespace pythonic {

    namespace numpy {

        template<class E>
            constexpr bool isscalar(E const&);

        PROXY_DECL(pythonic::numpy, isscalar);

    }

}

#endif
