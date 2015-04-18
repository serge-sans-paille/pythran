#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_LSTRIP_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_LSTRIP_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace str {
            types::str lstrip(types::str const& self, types::str const& to_del=" ");

            PROXY_DECL(pythonic::__builtin__::str, lstrip);

        }

    }

}
#endif
