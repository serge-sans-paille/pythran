#ifndef PYTHONIC_SET_ADD_HPP
#define PYTHONIC_SET_ADD_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __set__ {

        template<class T, class F>
            void add(types::set<T> &s, F const& value) {
                s.add(value);
            }
        template<class T, class F>
            void add(types::set<T> &&s, F const& value) {
                s.add(value);
            }
        PROXY(pythonic::__set__, add);

    }

}

#endif

