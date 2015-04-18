#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __builtin__ {

        namespace {
            types::file file(types::str const& filename, types::str const& strmode="r");
        }

        PROXY_DECL(pythonic::__builtin__, file);

    }

}

#endif
