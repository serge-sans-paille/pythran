#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_SYMMETRICDIFFERENCEUPDATE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_SYMMETRICDIFFERENCEUPDATE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace set {

            template<typename T, typename U>
                void
                symmetric_difference_update(types::set<T> & set, U const& other);

            template<typename T, typename U>
                void
                symmetric_difference_update(types::set<T> && set, U const& other);

            template<typename U>
                void
                symmetric_difference_update(types::empty_set const& set, U const& other);

            PROXY_DECL(pythonic::__builtin__::set, symmetric_difference_update);

        }

    }

}
#endif 
