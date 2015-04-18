#ifndef PYTHONIC_BUILTIN_RUNTIMEWARNING_HPP
#define PYTHONIC_BUILTIN_RUNTIMEWARNING_HPP

#include "pythonic/types/exceptions.hpp"
#include "pythran/pythonic/include/__builtin__/RuntimeWarning.hpp"

namespace pythonic {

    namespace __builtin__ {

        PYTHONIC_EXCEPTION_IMPL(RuntimeWarning)

    }

}

#endif

