#ifndef PYTHONIC_BUILTIN_DICT_VIEWITEMS_HPP
#define PYTHONIC_BUILTIN_DICT_VIEWITEMS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/dict.hpp"

#include "pythonic/include/__builtin__/dict/viewitems.hpp"

namespace pythonic {

    namespace __builtin__ {

        namespace dict {

            template<class K, class V>
                types::dict_items<types::dict<K,V>> viewitems(types::dict<K,V> const &d)
                {
                    return d.viewitems();
                }

            PROXY_IMPL(pythonic::__builtin__::dict, viewitems);
        }

    }

}

#endif
