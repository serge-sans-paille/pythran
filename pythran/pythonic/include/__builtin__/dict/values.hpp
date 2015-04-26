#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_VALUES_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_VALUES_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/dict.hpp"
#include "pythonic/types/list.hpp"

namespace pythonic {

    namespace __builtin__ {

        namespace dict {
            template<class K, class V>
                types::list<V> values(types::dict<K,V> const &d);

            PROXY_DECL(pythonic::__builtin__::dict, values);
        }

    }

}

#endif
