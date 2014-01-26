#ifndef PYTHONIC_SET_ISSUPERSET_HPP
#define PYTHONIC_SET_ISSUPERSET_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __set__ {
        template<class T, class U>
            bool issuperset(types::set<T> const& set, types::set<U> const& other){
                return set.issuperset(other);
            }
        PROXY(pythonic::__set__, issuperset);

    }

}

#endif

