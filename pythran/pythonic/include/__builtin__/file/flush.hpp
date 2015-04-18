#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_FLUSH_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_FLUSH_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace file {

            void flush(types::file &f);
            void flush(types::file &&f);

            PROXY_DECL(pythonic::__builtin__::file, flush);
        }

    }

}
#endif
