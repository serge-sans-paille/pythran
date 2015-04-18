#ifndef PYTHONIC_BUILTIN_DICT_ITEMS_HPP
#define PYTHONIC_BUILTIN_DICT_ITEMS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/dict.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/include/__builtin__/dict/items.hpp"

namespace pythonic {

    namespace __builtin__ {

        namespace dict {

            template<class K, class V>
                types::list<std::tuple<K,V>> items(types::dict<K,V> const &d)
                {
                    return types::list<std::tuple<K,V>>(d.item_begin(), d.item_end());
                }

            PROXY_IMPL(pythonic::__builtin__::dict, items);
        }

    }

}

#endif
