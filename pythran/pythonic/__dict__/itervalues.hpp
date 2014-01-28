#ifndef PYTHONIC_DICT_ITERVALUES_HPP
#define PYTHONIC_DICT_ITERVALUES_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/dict.hpp"

namespace pythonic {

    namespace __dict__ {
        template<class K, class V>
            auto itervalues(types::dict<K,V> d) -> decltype(d.itervalues()){
                return d.itervalues();
            }
        PROXY(pythonic::__dict__, itervalues);

    }

}

#endif

