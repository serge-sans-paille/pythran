#ifndef PYTHONIC_BUILTIN_EOFERROR_HPP
#define PYTHONIC_BUILTIN_EOFERROR_HPP

#include "pythonic/types/exceptions.hpp"
#include "pythran/pythonic/include/__builtin__/EOFError.hpp"

namespace pythonic {

    namespace __builtin__ {

        PYTHONIC_EXCEPTION_IMPL(EOFError)

    }

}

#endif

