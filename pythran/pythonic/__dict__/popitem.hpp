#ifndef PYTHONIC_DICT_POPITEM_HPP
#define PYTHONIC_DICT_POPITEM_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/dict.hpp"

namespace pythonic {

    namespace __dict__ {
        template<class K, class V>
            std::tuple<K,V> popitem(types::dict<K,V> d) {
                return d.popitem();
            }
        PROXY(pythonic::__dict__, popitem);

    }

}

#endif

