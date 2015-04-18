#ifndef PYTHONIC_INCLUDE_BUILTIN_ORD_HPP
#define PYTHONIC_INCLUDE_BUILTIN_ORD_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __builtin__ {
        long ord(types::str const & v);

        long ord(char v);

        PROXY_DECL(pythonic::__builtin__, ord);
    }

}

#endif
