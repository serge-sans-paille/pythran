#ifndef PYTHONIC_DICT_ITERVALUES_HPP
#define PYTHONIC_DICT_ITERVALUES_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/dict.hpp"

namespace pythonic {
namespace __builtin__ {

    namespace dict {
        template<class K, class V>
            auto itervalues(types::dict<K,V> d) -> decltype(d.itervalues()){
                return d.itervalues();
            }
        PROXY(pythonic::__builtin__::dict, itervalues);
    }

    }

}

#endif

