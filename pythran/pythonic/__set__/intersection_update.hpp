#ifndef PYTHONIC_SET_INTERSECTIONUPDATE_HPP
#define PYTHONIC_SET_INTERSECTIONUPDATE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __set__ {
        template<typename T, typename... Types>
            void intersection_update(types::set<T> & set, Types const&... others){
                set.intersection_update(others...);
            }
        template<typename T, typename... Types>
            void intersection_update(types::set<T> && set, Types const&... others){
                //If it is an rvalue, we don't really want to update
            }
        template<typename... Types>
            void intersection_update(types::empty_set && set, Types const&... others){
                //If it is an empty_set, it is not really updated otherwise we have a typing issue
            }
        PROXY(pythonic::__set__, intersection_update);

    }

}

#endif

