#ifndef PYTHONIC_BUILTIN_ABS_HPP
#define PYTHONIC_BUILTIN_ABS_HPP

#include "pythonic/utils/proxy.hpp"

#include <nt2/include/functions/abs.hpp>

namespace pythonic {

    namespace __builtin__ {

        using nt2::abs;
        PROXY(pythonic::__builtin__, abs);

    }

}

#endif

