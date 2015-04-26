#ifndef PYTHONIC_BUILTIN_FILE_NEXT_HPP
#define PYTHONIC_BUILTIN_FILE_NEXT_HPP

#include "pythonic/include/__builtin__/file/next.hpp"

#include "pythonic/__dispatch__/next.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace file {

            ALIAS(next, pythonic::__dispatch__::next);

            PROXY_IMPL(pythonic::__builtin__::file, next);
        }

    }

}
#endif
