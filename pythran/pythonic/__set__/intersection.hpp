#ifndef PYTHONIC_SET_INTERSECTION_HPP
#define PYTHONIC_SET_INTERSECTION_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __set__ {
        template<typename T, typename... Types> 
            types::set<T> intersection(types::set<T> const& set, Types const&... others){
                return set.intersection(others...);
            }
        PROXY(pythonic::__set__, intersection);

    }

}

#endif

