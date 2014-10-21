#ifndef PYTHONIC_DICT_VIEWVALUES_HPP
#define PYTHONIC_DICT_VIEWVALUES_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/dict.hpp"

namespace pythonic {
namespace __builtin__ {

    namespace dict {
        template<class K, class V>
            types::dict_values<types::dict<K,V>> viewvalues(types::dict<K,V> const &d) {
                return d.viewvalues();
            }
        PROXY(pythonic::__builtin__::dict, viewvalues);
    }

    }

}

#endif

