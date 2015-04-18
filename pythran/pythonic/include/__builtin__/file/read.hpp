#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_READ_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_READ_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace file {

            types::str read(types::file &f, int size=-1);
            types::str read(types::file &&f, int size=-1);

            PROXY_DECL(pythonic::__builtin__::file, read);

        }

    }

}
#endif
