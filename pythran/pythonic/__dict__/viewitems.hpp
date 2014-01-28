#ifndef PYTHONIC_DICT_VIEWITEMS_HPP
#define PYTHONIC_DICT_VIEWITEMS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/dict.hpp"

namespace pythonic {

    namespace __dict__ {
        template<class K, class V>
            types::dict_items<types::dict<K,V>> viewitems(types::dict<K,V> const &d) {
                return d.viewitems();
            }
        PROXY(pythonic::__dict__, viewitems);

    }

}

#endif

