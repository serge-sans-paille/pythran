#ifndef PYTHONIC_BUILTIN_DICT_POPITEM_HPP
#define PYTHONIC_BUILTIN_DICT_POPITEM_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/dict.hpp"
#include "pythonic/types/tuple.hpp"
#include "pythonic/include/__builtin__/dict/popitem.hpp"

namespace pythonic {

    namespace __builtin__ {

        namespace dict {

            template<class K, class V>
                std::tuple<K,V> popitem(types::dict<K,V> d)
                {
                    return d.popitem();
                }

            PROXY_IMPL(pythonic::__builtin__::dict, popitem);
        }

    }

}

#endif

