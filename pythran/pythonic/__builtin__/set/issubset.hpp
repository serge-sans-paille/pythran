#ifndef PYTHONIC_BUILTIN_SET_ISSUBSET_HPP
#define PYTHONIC_BUILTIN_SET_ISSUBSET_HPP

#include "pythonic/include/__builtin__/set/issubset.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace set {

            template<class T, class U>
                bool issubset(types::set<T> const& set, U const& other)
                {
                    return set.issubset(other);
                }

            template<class U>
                bool issubset(types::empty_set const& set, U const& other)
                {
                    return true;
                }

            PROXY_IMPL(pythonic::__builtin__::set, issubset);

        }

    }

}
#endif 

