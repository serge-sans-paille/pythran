#ifndef PYTHONIC_BUILTIN_GETATTR_HPP
#define PYTHONIC_BUILTIN_GETATTR_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/attr.hpp"

namespace pythonic {

    namespace __builtin__ {

        template<class T, size_t AttributeID>
            void getattr(T const & self);
    }

}
#endif
