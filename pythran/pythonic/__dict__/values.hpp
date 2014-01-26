#ifndef PYTHONIC_DICT_VALUES_HPP
#define PYTHONIC_DICT_VALUES_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/dict.hpp"
#include "pythonic/types/list.hpp"

namespace pythonic {

    namespace __dict__ {
        template<class K, class V>
            types::list<V> values(types::dict<K,V> const &d) {
                return types::list<V>(d.value_begin(), d.value_end());
            }
        PROXY(pythonic::__dict__, values);

    }

}

#endif

