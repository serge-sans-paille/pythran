#ifndef PYTHONIC_BUILTIN_FILE_READ_HPP
#define PYTHONIC_BUILTIN_FILE_READ_HPP

#include "pythonic/include/__builtin__/file/read.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace file {

            types::str read(types::file &f, int size)
            {
                return f.read(size);
            }
            types::str read(types::file &&f, int size)
            {
                return f.read(size);
            }

            PROXY_IMPL(pythonic::__builtin__::file, read);

        }

    }

}
#endif
