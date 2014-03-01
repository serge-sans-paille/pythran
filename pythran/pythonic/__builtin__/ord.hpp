#ifndef PYTHONIC_BUILTIN_ORD_HPP
#define PYTHONIC_BUILTIN_ORD_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/__builtin__/TypeError.hpp"
#include <sstream>

namespace pythonic {

    namespace __builtin__ {
        long ord(types::str const & v) {
            if(v.size() != 1) {
                std::ostringstream oss;
                oss << "ord() expected a character, but string of length " << v.size() << " found";
                throw types::TypeError(oss.str());
            }
            return (long)v[0];
        }
        long ord(char v) {
            return v;
        }
        PROXY(pythonic::__builtin__, ord);

    }

}

#endif

