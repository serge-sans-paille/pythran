#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_ISSUPERSET_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_ISSUPERSET_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace set {

            template<class T, class U>
                bool issuperset(types::set<T> const& set, U const& other);

            template<class U>
                bool issuperset(types::empty_set const& set, U const& other);

            PROXY_DECL(pythonic::__builtin__::set, issuperset);

        }

    }

}
#endif 
