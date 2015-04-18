#ifndef PYTHONIC_BUILTIN_OVERFLOWERROR_HPP
#define PYTHONIC_BUILTIN_OVERFLOWERROR_HPP

#include "pythonic/types/exceptions.hpp"
#include "pythran/pythonic/include/__builtin__/OverflowError.hpp"

namespace pythonic {

    namespace __builtin__ {

        PYTHONIC_EXCEPTION_IMPL(OverflowError)

    }

}

#endif

