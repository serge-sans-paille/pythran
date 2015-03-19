#ifndef PYTHONIC_BUILTIN_CHR_HPP
#define PYTHONIC_BUILTIN_CHR_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/include/__builtin__/chr.hpp"

namespace pythonic {

    namespace __builtin__ {
        template<class T>
            types::str chr(T const &v)
            {
                return types::str((char)v);
            }

        PROXY_IMPL(pythonic::__builtin__, chr);

    }

}

#endif
