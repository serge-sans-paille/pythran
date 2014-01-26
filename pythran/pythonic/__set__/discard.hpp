#ifndef PYTHONIC_SET_DISCARD_HPP
#define PYTHONIC_SET_DISCARD_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __set__ {
        template<class T, class U>
            void discard(types::set<T> & set, U const& elem){
                set.discard(elem);
            }
        template<class T, class U>
            void discard(types::set<T> && set, U const& elem){
                set.discard(elem);
            }
        PROXY(pythonic::__set__, discard);

    }

}

#endif

