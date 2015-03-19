#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_ISALPHA_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_ISALPHA_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace str {

            bool isalpha(types::str const& s);

            PROXY_DECL(pythonic::__builtin__::str, isalpha);

        }
    }
}
#endif
