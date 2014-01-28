#ifndef PYTHONIC_BUILTIN_OPEN_HPP
#define PYTHONIC_BUILTIN_OPEN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic {

    namespace __builtin__ {
        types::file open(types::str const& filename, types::str const& strmode = "r"){
            return types::file(filename, strmode);
        }
        PROXY(pythonic::__builtin__, open);

    }

}

#endif

