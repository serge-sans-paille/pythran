#ifndef PYTHONIC_BUILTIN_UNICODEWARNING_HPP
#define PYTHONIC_BUILTIN_UNICODEWARNING_HPP

#include "pythonic/types/exceptions.hpp"
#include "pythran/pythonic/include/__builtin__/UnicodeWarning.hpp"

namespace pythonic {

    namespace __builtin__ {

        PYTHONIC_EXCEPTION_IMPL(UnicodeWarning)

    }

}

#endif

