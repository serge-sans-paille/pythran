#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_RSTRIP_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_RSTRIP_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace str {

            types::str
            rstrip(types::str const& self, types::str const& to_del=" ");

            PROXY_DECL(pythonic::__builtin__::str, rstrip);

        }

    }

}
#endif
