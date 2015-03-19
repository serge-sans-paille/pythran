#ifndef PYTHONIC_BUILTIN_ABS_HPP
#define PYTHONIC_BUILTIN_ABS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/include/__builtin__/abs.hpp"

#include <nt2/include/functions/abs.hpp>

namespace pythonic {

    namespace __builtin__ {

        ALIAS(abs, nt2::abs);
        PROXY_IMPL(pythonic::__builtin__, abs);

    }

}

#endif
