#ifndef PYTHONIC_BUILTIN_LOOKUPERROR_HPP
#define PYTHONIC_BUILTIN_LOOKUPERROR_HPP

#include "pythonic/types/exceptions.hpp"
#include "pythran/pythonic/include/__builtin__/LookupError.hpp"

namespace pythonic {

    namespace __builtin__ {

        PYTHONIC_EXCEPTION_IMPL(LookupError)

    }

}

#endif

