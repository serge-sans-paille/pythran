#ifndef PYTHONIC_BUILTIN_SET_DIFFERENCEUPDATE_HPP
#define PYTHONIC_BUILTIN_SET_DIFFERENCEUPDATE_HPP

#include "pythonic/include/__builtin__/set/difference_update.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace set {

            template<typename T, typename... Types>
                void
                difference_update(types::set<T> & set, Types const&... others)
                {
                    set.difference_update(others...);
                }

            template<typename T, typename... Types>
                void
                difference_update(types::set<T> && set, Types const&... others)
                {
                    //nothing to be done as we work on rvalue
                }
            template<typename... Types>
                void
                difference_update(types::empty_set const& set, Types const&... others)
                {
                    //nothing can be removed in set
                }

            PROXY_IMPL(pythonic::__builtin__::set, difference_update);

        }

    }

}
#endif 
