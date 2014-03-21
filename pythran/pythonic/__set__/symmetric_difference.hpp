#ifndef PYTHONIC_SET_SYMMETRICDIFFERENCE_HPP
#define PYTHONIC_SET_SYMMETRICDIFFERENCE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __set__ {
        template<typename T, typename U>
            auto symmetric_difference(types::set<T> const& set, U const& other) -> decltype(set.symmetric_difference(other))
            {
                return set.symmetric_difference(other);
            }
        /* No rvalue overload possible because of return type modification.:
         * >>> a = set([1, 2, 3])
         * >>> b = set([2., 3., 4.])
         * >>> a.symmetric_difference(b)
         * set([1.0, 4.0])
         */
        template<typename U>
            typename __combined<types::empty_set, U>::type symmetric_difference(types::empty_set const& set, U const& other){
                // combiner is used as other may be list but return is a set
                return other;
            }
        types::empty_set symmetric_difference(types::empty_set const& set, types::empty_set const& other){
            return types::empty_set();
            }
        PROXY(pythonic::__set__, symmetric_difference);

    }

}

#endif

