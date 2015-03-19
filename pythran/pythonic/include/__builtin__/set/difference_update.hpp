#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_DIFFERENCEUPDATE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_DIFFERENCEUPDATE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace set {

            template<typename T, typename... Types>
                void
                difference_update(types::set<T> & set, Types const&... others);

            template<typename T, typename... Types>
                void
                difference_update(types::set<T> && set, Types const&... others);

            template<typename... Types>
                void
                difference_update(types::empty_set const& set, Types const&... others);

            PROXY_DECL(pythonic::__builtin__::set, difference_update);

        }

    }

}
#endif 
