#ifndef PYTHONIC_SET_DIFFERENCEUPDATE_HPP
#define PYTHONIC_SET_DIFFERENCEUPDATE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __set__ {
        template<typename T, typename... Types> 
            void difference_update(types::set<T> & set, Types const&... others){
                return set.difference_update(others...);
            }
        template<typename T, typename... Types> 
            void difference_update(types::set<T> && set, Types const&... others){
                return set.difference_update(others...);
            }
        PROXY(pythonic::__set__, difference_update);

    }

}

#endif

