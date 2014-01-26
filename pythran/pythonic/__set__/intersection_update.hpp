#ifndef PYTHONIC_SET_INTERSECTIONUPDATE_HPP
#define PYTHONIC_SET_INTERSECTIONUPDATE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __set__ {
        template<typename T, typename... Types> 
            void intersection_update(types::set<T> & set, Types const&... others){
                return set.intersection_update(others...);
            }
        template<typename T, typename... Types> 
            void intersection_update(types::set<T> && set, Types const&... others){
                return set.intersection_update(others...);
            }
        PROXY(pythonic::__set__, intersection_update);

    }

}

#endif

