#ifndef PYTHONIC_BUILTIN_ALL_HPP
#define PYTHONIC_BUILTIN_ALL_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __builtin__ {

        template <class Iterable>
            bool all( Iterable && s) {
                auto iend = s.end();
                for(auto iter = s.begin() ; iter != iend ; ++iter)
                    if( not *iter ) return false;
                return true;
            }
        PROXY(pythonic::__builtin__, all);

    }

}

#endif

