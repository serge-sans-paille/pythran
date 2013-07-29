#ifndef PYTHONIC_BUILTIN_BIN_HPP
#define PYTHONIC_BUILTIN_BIN_HPP

#include "pythonic/utils/proxy.hpp"

#include "pythonic/types/str.hpp"

#include <sstream>

namespace pythonic {

    namespace __builtin__ {
        template<class T>
            types::str bin(T const &v) {
                long unsigned int i = 1L << (8*sizeof(T)-1);
                while(i and not (v&i)) i>>=1;
                if(not i) return "0b0";
                else {
                    std::ostringstream oss;
                    oss << "0b";
                    for(; i ; i>>=1)
                        if(v & i) oss << "1";
                        else oss << "0";
                    return oss.str();
                }
            }
        PROXY(pythonic::__builtin__, bin);

    }

}

#endif

