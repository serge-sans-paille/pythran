#ifndef PYTHONIC_STR_CAPITALIZE_HPP
#define PYTHONIC_STR_CAPITALIZE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __str__ {
        types::str capitalize(types::str const & s)
        {
            if(s.empty()) return s;
            else {
                types::str copy = s;
                copy[0] = ::toupper(s[0]);
                std::transform(s.begin()+1, s.end(), copy.begin()+1, ::tolower);
                return copy;
            }
        }
        PROXY(pythonic::__str__, capitalize);

    }

}

#endif

