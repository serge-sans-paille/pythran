#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_ITERITEMS_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_ITERITEMS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/dict.hpp"

namespace pythonic {

    namespace __builtin__ {

        namespace dict {

            template<class K, class V>
                auto iteritems(types::dict<K,V> d) -> decltype(d.iteritems());

            PROXY_DECL(pythonic::__builtin__::dict, iteritems);
        }

    }

}

#endif
