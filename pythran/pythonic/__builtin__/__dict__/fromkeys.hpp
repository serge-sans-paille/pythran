#ifndef PYTHONIC_BUILTIN_DICT_FROMKEYS_HPP
#define PYTHONIC_BUILTIN_DICT_FROMKEYS_HPP

#include "pythonic/utils/proxy.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/__builtin__/None.hpp"

namespace pythonic {

    namespace __builtin__ {

        namespace __dict__ {
            template<class Iterable, class V=types::none_type>
                types::dict<typename std::remove_reference<Iterable>::type::value_type, V> fromkeys(Iterable && iter, V const & v = None) {
                    types::dict<typename std::remove_reference<Iterable>::type::value_type,V> D;
                    D=types::empty_dict();
                    for(auto const& i: iter) D[i]=v;
                    return D;
                }
            PROXY(pythonic::__builtin__::__dict__, fromkeys);

        }
    }

}

#endif

