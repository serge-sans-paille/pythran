#ifndef PYTHONIC_DICT_FROMKEYS_HPP
#define PYTHONIC_DICT_FROMKEYS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/dict.hpp"
#include "pythonic/__builtin__/None.hpp"

namespace pythonic {

    namespace __dict__ {
        template<class Iterable, class V=types::none_type>
            types::dict<typename std::remove_reference<Iterable>::type::value_type, V> fromkeys(Iterable && iter, V const & v = __builtin__::None) {
                types::dict<typename std::remove_reference<Iterable>::type::value_type,V> D;
                D=types::empty_dict();
                for(auto const& i: iter) D[i]=v;
                return D;
            }
        PROXY(pythonic::__dict__, fromkeys);

    }

}

#endif

