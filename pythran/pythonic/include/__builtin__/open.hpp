#ifndef PYTHONIC_INCLUDE_BUILTIN_OPEN_HPP
#define PYTHONIC_INCLUDE_BUILTIN_OPEN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic {

    namespace __builtin__ {

        types::file
        open(types::str const& filename, types::str const& strmode = "r");

        PROXY_DECL(pythonic::__builtin__, open);
    }

}

#endif
