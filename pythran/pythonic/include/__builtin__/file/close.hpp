#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_CLOSE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_CLOSE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace file {

            void close(types::file &f);
            void close(types::file &&f);

            PROXY_DECL(pythonic::__builtin__::file, close);

        }

    }

}
#endif
