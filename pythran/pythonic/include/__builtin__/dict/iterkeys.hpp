#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_ITERKEYS_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_ITERKEYS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/dict.hpp"

namespace pythonic {

    namespace __builtin__ {

        namespace dict {
            template<class K, class V>
                auto iterkeys(types::dict<K,V> d) -> decltype(d.iterkeys());

            PROXY_DECL(pythonic::__builtin__::dict, iterkeys);
        }

    }

}

#endif
