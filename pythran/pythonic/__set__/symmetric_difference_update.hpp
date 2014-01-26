#ifndef PYTHONIC_SET_SYMMETRICDIFFERENCEUPDATE_HPP
#define PYTHONIC_SET_SYMMETRICDIFFERENCEUPDATE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __set__ {
        template<typename T, typename U> 
            void symmetric_difference_update(types::set<T> & set, U const& other){
                return set.symmetric_difference_update(other);
            }
        template<typename T, typename U> 
            void symmetric_difference_update(types::set<T> && set, U const& other){
                return set.symmetric_difference_update(other);
            }
        PROXY(pythonic::__set__, symmetric_difference_update);

    }

}

#endif

