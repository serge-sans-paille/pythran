#ifndef PYTHONIC_SET_ISSUBSET_HPP
#define PYTHONIC_SET_ISSUBSET_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __set__ {
        template<class T, class U>
            bool issubset(types::set<T> const& set, U const& other){
                return set.issubset(other);
            }
        template<class U>
            bool issubset(types::empty_set const& set, U const& other){
                return true;
            }
        PROXY(pythonic::__set__, issubset);

    }

}

#endif

