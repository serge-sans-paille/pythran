#ifndef PYTHONIC_BUILTIN_FILE_READLINE_HPP
#define PYTHONIC_BUILTIN_FILE_READLINE_HPP

#include "pythonic/include/__builtin__/file/readline.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace file {

            types::str readline(types::file &f, long size)
            {
                return size < 0 ? f.readline() : f.readline(size);
            }

            types::str readline(types::file &&f, long size)
            {
                return size < 0 ? f.readline() : f.readline(size);
            }

            PROXY_IMPL(pythonic::__builtin__::file, readline);

        }

    }

}
#endif
