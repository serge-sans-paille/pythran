#ifndef PYTHONIC_DICT_SETDEFAULT_HPP
#define PYTHONIC_DICT_SETDEFAULT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/dict.hpp"

namespace pythonic {

    namespace __dict__ {
        template<class K, class V, class W, class X>
            V setdefault(types::dict<K,V> &d, W const & k, X const &default_) {
                return d.setdefault(k,default_);
            }
        template<class K, class V, class W>
            V setdefault(types::dict<K,V> &d, W const & k) {
                return d.get(k);
            }
        template<class K, class V, class W, class X>
            V setdefault(types::dict<K,V> &&d, W const & k, X const &default_) {
                return d.setdefault(k,default_);
            }
        template<class K, class V, class W>
            V setdefault(types::dict<K,V> &&d, W const & k) {
                return d.get(k);
            }
        PROXY(pythonic::__dict__, setdefault);

    }

}

#endif

