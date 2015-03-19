#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_POPITEM_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_POPITEM_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/dict.hpp"
#include "pythonic/types/tuple.hpp"

namespace pythonic {

    namespace __builtin__ {

        namespace dict {

            template<class K, class V>
                std::tuple<K,V> popitem(types::dict<K,V> d);

            PROXY_DECL(pythonic::__builtin__::dict, popitem);
        }

    }

}

#endif
