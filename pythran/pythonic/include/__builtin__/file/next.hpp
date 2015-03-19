#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_NEXT_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_NEXT_HPP

#include "pythonic/__dispatch__/next.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace file {

            ALIAS_DECL(next, pythonic::__dispatch__::next);

            PROXY_DECL(pythonic::__builtin__::file, next);
        }

    }

}
#endif
