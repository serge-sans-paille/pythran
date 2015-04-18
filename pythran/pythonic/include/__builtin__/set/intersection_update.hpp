#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_INTERSECTIONUPDATE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_INTERSECTIONUPDATE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace set {

            template<typename T, typename... Types>
                void
                intersection_update(types::set<T> & set, Types const&... others);

            template<typename T, typename... Types>
                void
                intersection_update(types::set<T> && set, Types const&... others);

            template<typename... Types>
                void
                intersection_update(types::empty_set && set, Types const&... others);

            PROXY_DECL(pythonic::__builtin__::set, intersection_update);

        }

    }

}
#endif 
