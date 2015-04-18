#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_XREADLINES_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_XREADLINES_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace file {

            types::file& xreadlines(types::file &f);
            types::file&& xreadlines(types::file &&f);

            PROXY_DECL(pythonic::__builtin__::file, xreadlines);
        }

    }

}
#endif
