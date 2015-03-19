#ifndef PYTHONIC_INCLUDE_BUILTIN_ABS_HPP
#define PYTHONIC_INCLUDE_BUILTIN_ABS_HPP

#include "pythonic/utils/proxy.hpp"

#include <nt2/include/functions/abs.hpp>

namespace pythonic {

    namespace __builtin__ {

        ALIAS_DECL(abs, nt2::abs);
        PROXY_DECL(pythonic::__builtin__, abs);

    }

}

#endif
