#ifndef PYTHONIC_BUILTIN_IMPORTERROR_HPP
#define PYTHONIC_BUILTIN_IMPORTERROR_HPP

#include "pythonic/types/exceptions.hpp"
#include "pythran/pythonic/include/__builtin__/ImportError.hpp"

namespace pythonic {

    namespace __builtin__ {

        PYTHONIC_EXCEPTION_IMPL(ImportError)

    }

}

#endif

