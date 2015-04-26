#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_READLINE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_READLINE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace file {

            types::str readline(types::file &f, long size=-1);
            types::str readline(types::file &&f, long size=-1);

            PROXY_DECL(pythonic::__builtin__::file, readline);

        }

    }

}
#endif
