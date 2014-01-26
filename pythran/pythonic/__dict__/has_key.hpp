#ifndef PYTHONIC_DICT_HASKEY_HPP
#define PYTHONIC_DICT_HASKEY_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/dict.hpp"

namespace pythonic {

    namespace __dict__ {
        template<class K, class V, class W>
            bool has_key(types::dict<K,V> const &d, W const& k) {
                return d.find(k) != d.item_end();
            }
        PROXY(pythonic::__dict__, has_key);

    }

}

#endif

