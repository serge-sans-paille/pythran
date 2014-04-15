#ifndef PYTHONIC_BUILTIN_BOOL_HPP
#define PYTHONIC_BUILTIN_BOOL_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/bool.hpp"

namespace pythonic {

    namespace __builtin__ {
        template<class T>
            bool bool_(T&& val) { return val; }

        bool bool_() { return false; }

        PROXY(pythonic::__builtin__, bool_);
    }

}

#endif

