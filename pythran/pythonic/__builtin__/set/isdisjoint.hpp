#ifndef PYTHONIC_BUILTIN_SET_ISDISJOINT_HPP
#define PYTHONIC_BUILTIN_SET_ISDISJOINT_HPP

#include "pythonic/include/__builtin__/set/isdisjoint.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace set {

            template<class T, class U>
                bool
                isdisjoint(types::set<T> const& calling_set, U const& arg_set)
                {
                    return calling_set.isdisjoint(arg_set);
                }

            template<class U>
                bool
                isdisjoint(types::empty_set const& calling_set, U const& arg_set)
                {
                    return true;
                }

            PROXY_IMPL(pythonic::__builtin__::set, isdisjoint);

        }

    }

}
#endif 
