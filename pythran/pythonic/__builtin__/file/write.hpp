#ifndef PYTHONIC_BUILTIN_FILE_WRITE_HPP
#define PYTHONIC_BUILTIN_FILE_WRITE_HPP

#include "pythonic/include/__builtin__/file/write.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace file {

            void write(types::file & f, types::str const& str)
            {
                f.write(str);
            }

            void write(types::file && f, types::str const& str)
            {
                f.write(str);
            }

            PROXY_IMPL(pythonic::__builtin__::file, write);
        }

    }

}
#endif
