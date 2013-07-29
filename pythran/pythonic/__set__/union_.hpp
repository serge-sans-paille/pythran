#ifndef PYTHONIC_SET_UNION_HPP
#define PYTHONIC_SET_UNION_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __set__ {
        template<typename T, typename... Types> 
            types::set<T> union_(types::set<T> const& set, Types const&... others){
                return set.union_(others...);
            }
        PROXY(pythonic::__set__, union_);

    }

}

#endif

