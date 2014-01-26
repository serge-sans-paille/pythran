#ifndef PYTHONIC_DICT_ITEMS_HPP
#define PYTHONIC_DICT_ITEMS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/dict.hpp"
#include "pythonic/types/list.hpp"

namespace pythonic {

    namespace __dict__ {
        template<class K, class V>
            types::list< std::tuple<K,V> > items(types::dict<K,V> const &d) {
                return types::list< std::tuple<K,V> >(d.item_begin(), d.item_end());
            }
        PROXY(pythonic::__dict__, items);

    }

}

#endif

