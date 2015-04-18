#ifndef PYTHONIC_BUILTIN_NOTIMPLEMENTEDERROR_HPP
#define PYTHONIC_BUILTIN_NOTIMPLEMENTEDERROR_HPP

#include "pythonic/types/exceptions.hpp"
#include "pythran/pythonic/include/__builtin__/NotImplementedError.hpp"

namespace pythonic {

    namespace __builtin__ {

        PYTHONIC_EXCEPTION_IMPL(NotImplementedError)

    }

}

#endif

