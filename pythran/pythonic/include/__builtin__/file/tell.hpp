#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_TELL_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_TELL_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace file {

            long tell(types::file const& f);

            PROXY_DECL(pythonic::__builtin__::file, tell);
        }

    }

}
#endif
