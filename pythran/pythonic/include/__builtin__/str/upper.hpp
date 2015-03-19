#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_UPPER_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_UPPER_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace str {

            types::str upper(types::str const & s);

            PROXY_DECL(pythonic::__builtin__::str, upper);
        }

    }

}
#endif
