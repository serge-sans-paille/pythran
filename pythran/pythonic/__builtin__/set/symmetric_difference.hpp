#ifndef PYTHONIC_BUILTIN_SET_SYMMETRICDIFFERENCE_HPP
#define PYTHONIC_BUILTIN_SET_SYMMETRICDIFFERENCE_HPP

#include "pythonic/include/__builtin__/set/symmetric_difference.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace set {

            template<typename T, typename U>
                auto symmetric_difference(types::set<T> const& set, U const& other)
                -> decltype(set.symmetric_difference(other))
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
                typename __combined<types::empty_set, U>::type
                symmetric_difference(types::empty_set const& set, U const& other)
                {
                    return other;
                }

            PROXY_IMPL(pythonic::__builtin__::set, symmetric_difference);

        }

    }

}
#endif 
