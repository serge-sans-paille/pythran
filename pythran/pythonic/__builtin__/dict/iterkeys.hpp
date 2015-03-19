#ifndef PYTHONIC_BUILTIN_DICT_ITERKEYS_HPP
#define PYTHONIC_BUILTIN_DICT_ITERKEYS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/dict.hpp"
#include "pythonic/include/__builtin__/dict/iterkeys.hpp"

namespace pythonic {

    namespace __builtin__ {

        namespace dict {
            template<class K, class V>
                auto iterkeys(types::dict<K,V> d) -> decltype(d.iterkeys())
                {
                    return d.iterkeys();
                }

            PROXY_IMPL(pythonic::__builtin__::dict, iterkeys);
        }

    }

}

#endif
