#ifndef PYTHONIC_BUILTIN_SYSTEMEXIT_HPP
#define PYTHONIC_BUILTIN_SYSTEMEXIT_HPP

#include "pythonic/types/exceptions.hpp"
#include "pythran/pythonic/include/__builtin__/SystemExit.hpp"

namespace pythonic {

    namespace __builtin__ {

        PYTHONIC_EXCEPTION_IMPL(SystemExit)

    }

}

#endif

