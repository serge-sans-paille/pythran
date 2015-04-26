#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_GET_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_GET_HPP

#include "pythonic/utils/proxy.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/types/none.hpp"

namespace pythonic {

    namespace __builtin__ {

        namespace dict {

            template<class K, class V, class W, class X>
                V get(types::dict<K,V> const &d, W const& k, X const &default_);

            template<class K, class V, class W>
                types::none<V> get(types::dict<K,V> const &d, W const& k);

            template<class W, class X>
                X get(types::empty_dict const &, W const& , X const &default_);

            template<class T, class I, class J>
                typename __combined<T, J>::type get(::dict_container<T>, I , J);

            PROXY_DECL(pythonic::__builtin__::dict, get);

        }
    }

}

#endif

