#ifndef PYTHONIC_SET_ISSUBSET_HPP
#define PYTHONIC_SET_ISSUBSET_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __set__ {
        template<class T, class U>
            bool issubset(types::set<T> const& set, types::set<U> const& other){
                return set.issubset(other);
            }
        PROXY(pythonic::__set__, issubset);

    }

}

#endif

