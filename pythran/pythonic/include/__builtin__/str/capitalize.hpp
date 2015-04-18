#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_CAPITALIZE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_CAPITALIZE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace str {

            types::str capitalize(types::str const & s);

            PROXY_DECL(pythonic::__builtin__::str, capitalize);

        }

    }

}
#endif
