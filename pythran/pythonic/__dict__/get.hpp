#ifndef PYTHONIC_DICT_GET_HPP
#define PYTHONIC_DICT_GET_HPP

#include "pythonic/utils/proxy.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/types/none.hpp"

namespace pythonic {

    namespace __dict__ {
        template<class K, class V, class W, class X>
            V get(types::dict<K,V> const &d, W const& k, X const &default_) {
                return d.get(k,default_);
            }
        template<class K, class V, class W>
            types::none<V> get(types::dict<K,V> const &d, W const& k) {
                return d.get(k);
            }
        template<class W, class X>
            X get(types::empty_dict const &, W const& , X const &default_) {
                return default_;
            }
        template<class T, class I, class J>
            decltype(std::declval<T>()+std::declval<J>()) get(::dict_container<T>, I , J );
        PROXY(pythonic::__dict__, get);

    }

}

#endif

