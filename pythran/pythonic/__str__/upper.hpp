#ifndef PYTHONIC_STR_UPPER_HPP
#define PYTHONIC_STR_UPPER_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __str__ {
        types::str upper(types::str const & s)
        {
            types::str copy = s;
            std::transform(s.begin(),s.end(), copy.begin(), ::toupper);
            return copy;
        }
        PROXY(pythonic::__str__, upper);


    }

}

#endif

