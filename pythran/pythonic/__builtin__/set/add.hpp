#ifndef PYTHONIC_SET_ADD_HPP
#define PYTHONIC_SET_ADD_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic { namespace __builtin__  {

    namespace set {

        template<class T, class F>
            void add(types::set<T> &s, F const& value) {
                s.add(value);
            }
        template<class T, class F>
            void add(types::set<T> &&s, F const& value) {
                // nothing have to be done as we work on rvalue
            }
        PROXY(pythonic::__builtin__::set, add);

    }

}

}
#endif 

