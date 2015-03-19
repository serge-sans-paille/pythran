#ifndef PYTHONIC_INCLUDE_BUILTIN_CHR_HPP
#define PYTHONIC_INCLUDE_BUILTIN_CHR_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __builtin__ {
        template<class T>
            types::str chr(T const &v);

        PROXY_DECL(pythonic::__builtin__, chr);

    }

}

#endif
