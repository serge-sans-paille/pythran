#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_ITEMS_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_ITEMS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/dict.hpp"
#include "pythonic/types/list.hpp"

namespace pythonic {

    namespace __builtin__ {

        namespace dict {

            template<class K, class V>
                types::list<std::tuple<K,V>> items(types::dict<K,V> const &d);

            PROXY_DECL(pythonic::__builtin__::dict, items);
        }

    }

}

#endif
