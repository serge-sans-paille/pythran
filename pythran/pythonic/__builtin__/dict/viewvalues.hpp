#ifndef PYTHONIC_BUILTIN_DICT_VIEWVALUES_HPP
#define PYTHONIC_BUILTIN_DICT_VIEWVALUES_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/dict.hpp"
#include "pythonic/include/__builtin__/dict/viewvalues.hpp"

namespace pythonic {

    namespace __builtin__ {

        namespace dict {

            template<class K, class V>
                types::dict_values<types::dict<K,V>> viewvalues(types::dict<K,V> const &d)
                {
                    return d.viewvalues();
                }

            PROXY_IMPL(pythonic::__builtin__::dict, viewvalues);
        }

    }

}

#endif
