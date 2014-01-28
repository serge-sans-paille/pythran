#ifndef PYTHONIC_SET_SYMMETRICDIFFERENCE_HPP
#define PYTHONIC_SET_SYMMETRICDIFFERENCE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __set__ {
        template<typename T, typename U> 
            types::set<T> symmetric_difference(types::set<T> const& set, U const& other){
                return set.symmetric_difference(other);
            }
        PROXY(pythonic::__set__, symmetric_difference);

    }

}

#endif

