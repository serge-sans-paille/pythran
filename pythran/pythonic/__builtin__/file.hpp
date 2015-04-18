#ifndef PYTHONIC_BUILTIN_FILE_HPP
#define PYTHONIC_BUILTIN_FILE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/include/__builtin__/file.hpp"

namespace pythonic {

    namespace __builtin__ {

        namespace {
            types::file file(types::str const& filename, types::str const& strmode)
            {
                return types::file(filename, strmode);
            } 
        }

        PROXY_IMPL(pythonic::__builtin__, file);

    }

}

#endif
