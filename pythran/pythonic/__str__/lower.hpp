#ifndef PYTHONIC_STR_LOWER_HPP
#define PYTHONIC_STR_LOWER_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __str__ {
        types::str lower(types::str const & s)
        {
            types::str copy = s;
            std::transform(s.begin(),s.end(), copy.begin(), ::tolower);
            return copy;
        }
        PROXY(pythonic::__str__, lower);

    }

}

#endif

