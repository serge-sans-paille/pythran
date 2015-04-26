#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_ADD_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_ADD_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace set {

            template<class T, class F>
                void add(types::set<T> &s, F const& value);

            template<class T, class F>
                void add(types::set<T> &&s, F const& value);

            PROXY_DECL(pythonic::__builtin__::set, add);

        }

    }

}
#endif 
