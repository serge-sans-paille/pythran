#ifndef PYTHONIC_BUILTIN_DICT_KEYS_HPP
#define PYTHONIC_BUILTIN_DICT_KEYS_HPP

#include "pythonic/utils/proxy.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/types/list.hpp"

#include "pythonic/include/__builtin__/dict/keys.hpp"

namespace pythonic {

    namespace __builtin__ {

        namespace dict {

            template<class K, class V>
                types::list<K> keys(types::dict<K,V> const &d)
                {
                    return types::list<K>(d.key_begin(), d.key_end());
                }

            PROXY_IMPL(pythonic::__builtin__::dict, keys);
        }

    }

}

#endif
