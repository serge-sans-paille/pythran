#ifndef PYTHONIC_INCLUDE_BUILTIN_OCT_HPP
#define PYTHONIC_INCLUDE_BUILTIN_OCT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __builtin__ {
        template <class T>
            types::str oct(T const & v);

        PROXY_DECL(pythonic::__builtin__, oct);

    }

}

#endif
