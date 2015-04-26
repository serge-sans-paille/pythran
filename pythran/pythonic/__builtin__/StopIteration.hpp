#ifndef PYTHONIC_BUILTIN_STOPITERATION_HPP
#define PYTHONIC_BUILTIN_STOPITERATION_HPP

#include "pythonic/types/exceptions.hpp"
#include "pythran/pythonic/include/__builtin__/StopIteration.hpp"

namespace pythonic {

    namespace __builtin__ {

        PYTHONIC_EXCEPTION_IMPL(StopIteration)

    }

}

#endif

