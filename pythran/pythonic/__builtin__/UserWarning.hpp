#ifndef PYTHONIC_BUILTIN_USERWARNING_HPP
#define PYTHONIC_BUILTIN_USERWARNING_HPP

#include "pythonic/types/exceptions.hpp"
#include "pythran/pythonic/include/__builtin__/UserWarning.hpp"

namespace pythonic {

    namespace __builtin__ {

        PYTHONIC_EXCEPTION_IMPL(UserWarning)

    }

}

#endif

