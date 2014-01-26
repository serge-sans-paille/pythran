#ifndef PYTHONIC_SET_DIFFERENCE_HPP
#define PYTHONIC_SET_DIFFERENCE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __set__ {
        template<typename T, typename... Types> 
            types::set<T> difference(types::set<T> const& set, Types const&... others){
                return set.difference(others...);
            }
        PROXY(pythonic::__set__, difference);

    }

}

#endif

