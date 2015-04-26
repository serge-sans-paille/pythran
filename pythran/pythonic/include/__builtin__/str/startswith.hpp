#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_STARTSWITH_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_STARTSWITH_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace str {

            bool
            startswith(types::str const& s, types::str const& prefix, long start=0, long end=-1);

            PROXY_DECL(pythonic::__builtin__::str, startswith);
        }

    }

}
#endif
