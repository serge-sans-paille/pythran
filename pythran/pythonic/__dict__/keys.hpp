#ifndef PYTHONIC_DICT_KEYS_HPP
#define PYTHONIC_DICT_KEYS_HPP

#include "pythonic/utils/proxy.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/types/list.hpp"

namespace pythonic {

    namespace __dict__ {
        template<class K, class V>
            types::list<K> keys(types::dict<K,V> const &d) {
                return types::list<K>(d.key_begin(), d.key_end());
            }
        PROXY(pythonic::__dict__, keys);

    }

}

#endif

