#ifndef PYTHONIC_INCLUDE_BUILTIN_ROUND_HPP
#define PYTHONIC_INCLUDE_BUILTIN_ROUND_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __builtin__ {
        template <class T>
            double round(T const & v, size_t n=0);

        PROXY_DECL(pythonic::__builtin__, round);

    }

}

#endif
