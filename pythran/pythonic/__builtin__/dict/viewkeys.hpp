#ifndef PYTHONIC_DICT_VIEWKEYS_HPP
#define PYTHONIC_DICT_VIEWKEYS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/dict.hpp"

namespace pythonic {
namespace __builtin__ {

    namespace dict {
        template<class K, class V>
            types::dict_keys<types::dict<K,V>> viewkeys(types::dict<K,V> const &d) {
                return d.viewkeys();
            }
        PROXY(pythonic::__builtin__::dict, viewkeys);
    }

    }

}

#endif

