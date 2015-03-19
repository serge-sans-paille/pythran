#ifndef PYTHONIC_BUILTIN_DICT_HASKEY_HPP
#define PYTHONIC_BUILTIN_DICT_HASKEY_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/dict.hpp"
#include "pythonic/include/__builtin__/dict/has_key.hpp"

namespace pythonic {

    namespace __builtin__ {

        namespace dict {
            template<class K, class V, class W>
                bool has_key(types::dict<K,V> const &d, W const& k)
                {
                    return d.find(k) != d.item_end();
                }
            PROXY_IMPL(pythonic::__builtin__::dict, has_key);
        }

    }

}

#endif

