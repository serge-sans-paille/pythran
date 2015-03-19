#ifndef PYTHONIC_BUILTIN_OPEN_HPP
#define PYTHONIC_BUILTIN_OPEN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"
#include "pythonic/include/__builtin__/open.hpp"

namespace pythonic {

    namespace __builtin__ {

        types::file
        open(types::str const& filename, types::str const& strmode)
        {
            return types::file(filename, strmode);
        }

        PROXY_IMPL(pythonic::__builtin__, open);
    }

}

#endif
