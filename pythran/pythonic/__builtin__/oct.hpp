#ifndef PYTHONIC_BUILTIN_OCT_HPP
#define PYTHONIC_BUILTIN_OCT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

#include <sstream>

namespace pythonic {

    namespace __builtin__ {
        template <class T>
            types::str oct(T const & v) {
                std::ostringstream oss;
                oss << '0' << std::oct << v;
                return oss.str();
            }
        PROXY(pythonic::__builtin__, oct);

    }

}

#endif

