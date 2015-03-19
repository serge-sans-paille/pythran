#ifndef PYTHONIC_BUILTIN_FILE_SEEK_HPP
#define PYTHONIC_BUILTIN_FILE_SEEK_HPP

#include "pythonic/include/__builtin__/file/seek.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace file {

            void seek(types::file &f, long offset)
            {
                f.seek(offset);
            }

            void seek(types::file &&f, long offset)
            {
                f.seek(offset);
            }

            void seek(types::file &f, long offset, long whence)
            {
                f.seek(offset, whence);
            }

            void seek(types::file &&f, long offset, long whence)
            {
                f.seek(offset, whence);
            }

            PROXY_IMPL(pythonic::__builtin__::file, seek);

        }

    }

}
#endif
