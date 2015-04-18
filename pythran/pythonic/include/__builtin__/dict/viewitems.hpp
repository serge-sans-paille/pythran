#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_VIEWITEMS_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_VIEWITEMS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/dict.hpp"

namespace pythonic {

    namespace __builtin__ {

        namespace dict {

            template<class K, class V>
                types::dict_items<types::dict<K,V>> viewitems(types::dict<K,V> const &d);

            PROXY_DECL(pythonic::__builtin__::dict, viewitems);
        }

    }

}

#endif
