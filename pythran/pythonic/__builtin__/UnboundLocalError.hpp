#ifndef PYTHONIC_BUILTIN_UNBOUNDLOCALERROR_HPP
#define PYTHONIC_BUILTIN_UNBOUNDLOCALERROR_HPP

#include "pythonic/types/exceptions.hpp"
#include "pythran/pythonic/include/__builtin__/UnboundLocalError.hpp"

namespace pythonic {

    namespace __builtin__ {

        PYTHONIC_EXCEPTION_IMPL(UnboundLocalError)

    }

}

#endif

