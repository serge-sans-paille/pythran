#ifndef PYTHONIC_BUILTIN_MEMORYERROR_HPP
#define PYTHONIC_BUILTIN_MEMORYERROR_HPP

#include "pythonic/types/exceptions.hpp"
#include "pythran/pythonic/include/__builtin__/MemoryError.hpp"

namespace pythonic {

    namespace __builtin__ {

        PYTHONIC_EXCEPTION_IMPL(MemoryError)

    }

}

#endif

