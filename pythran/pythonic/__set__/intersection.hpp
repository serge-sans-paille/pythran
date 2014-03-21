#ifndef PYTHONIC_SET_INTERSECTION_HPP
#define PYTHONIC_SET_INTERSECTION_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __set__ {
        template<typename T, typename... Types>
            auto intersection(types::set<T> const& set, Types const&... others) -> decltype(set.intersection(others...))
            {
                return set.intersection(others...);
            }
        /* No rvalue overload possible because of return type modification.:
         * >>> a = set([1,2,3])
         * >>> b = set([1., 2., 3.])
         * >>> a.intersection(b)
         * set([1.0, 2.0, 3.0])
         */
        template<typename... Types>
            types::empty_set intersection(types::empty_set const& set, Types const&... others){
                return types::empty_set();
            }
        PROXY(pythonic::__set__, intersection);

    }

}

#endif

