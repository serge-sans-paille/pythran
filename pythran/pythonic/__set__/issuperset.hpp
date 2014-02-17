#ifndef PYTHONIC_SET_ISSUPERSET_HPP
#define PYTHONIC_SET_ISSUPERSET_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __set__ {
        template<class T, class U>
            bool issuperset(types::set<T> const& set, U const& other){
                return set.issuperset(other);
            }
        template<class U>
            bool issuperset(types::empty_set const& set, U const& other){
                return false;
            }
        PROXY(pythonic::__set__, issuperset);

    }

}

#endif

