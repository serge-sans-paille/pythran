#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_WRITE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_WRITE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace file {

            void write(types::file & f, types::str const& str);
            void write(types::file && f, types::str const& str);

            PROXY_DECL(pythonic::__builtin__::file, write);
        }

    }

}
#endif
