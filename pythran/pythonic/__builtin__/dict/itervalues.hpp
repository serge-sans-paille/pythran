#ifndef PYTHONIC_BUILTIN_DICT_ITERVALUES_HPP
#define PYTHONIC_BUILTIN_DICT_ITERVALUES_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/dict.hpp"
#include "pythonic/include/__builtin__/dict/itervalues.hpp"

namespace pythonic {

    namespace __builtin__ {

        namespace dict {

            template<class K, class V>
                auto itervalues(types::dict<K,V> d) -> decltype(d.itervalues())
                {
                    return d.itervalues();
                }

            PROXY_IMPL(pythonic::__builtin__::dict, itervalues);
        }

    }

}

#endif
