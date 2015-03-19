#ifndef PYTHONIC_BUILTIN_SET_INTERSECTIONUPDATE_HPP
#define PYTHONIC_BUILTIN_SET_INTERSECTIONUPDATE_HPP

#include "pythonic/include/__builtin__/set/intersection_update.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace set {

            template<typename T, typename... Types>
                void
                intersection_update(types::set<T> & set, Types const&... others)
                {
                    set.intersection_update(others...);
                }

            template<typename T, typename... Types>
                void
                intersection_update(types::set<T> && set, Types const&... others)
                {
                    //If it is an rvalue, we don't really want to update
                }

            template<typename... Types>
                void
                intersection_update(types::empty_set && set, Types const&... others)
                {
                    //If it is an empty_set, it is not really updated otherwise we have a typing issue
                }

            PROXY_IMPL(pythonic::__builtin__::set, intersection_update);

        }

    }

}
#endif 
