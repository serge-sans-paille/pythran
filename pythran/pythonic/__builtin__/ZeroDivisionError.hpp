#ifndef PYTHONIC_BUILTIN_ZERODIVISIONERROR_HPP
#define PYTHONIC_BUILTIN_ZERODIVISIONERROR_HPP

#include "pythonic/types/exceptions.hpp"
#include "pythran/pythonic/include/__builtin__/ZeroDivisionError.hpp"

namespace pythonic {

    namespace __builtin__ {

        PYTHONIC_EXCEPTION_IMPL(ZeroDivisionError)

    }

}

#endif

