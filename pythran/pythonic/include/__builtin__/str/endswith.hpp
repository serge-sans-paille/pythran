#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_ENDSWITH_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_ENDSWITH_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace str {

            bool endswith(types::str const& s, types::str const& suffix, long start=0, long end=-1);

            PROXY_DECL(pythonic::__builtin__::str, endswith);

        }

    }

}
#endif
