#ifndef PYTHONIC_BUILTIN_FILE_HPP
#define PYTHONIC_BUILTIN_FILE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic {

    namespace __builtin__ {
        types::file file(types::str const& filename, types::str const& strmode = "r") {
            return types::file(filename, strmode);
        } 
        PROXY(pythonic::__builtin__, file);

    }

}

#endif

