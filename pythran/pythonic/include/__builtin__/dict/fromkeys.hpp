#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_FROMKEYS_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_FROMKEYS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/dict.hpp"
#include "pythonic/__builtin__/None.hpp"

namespace pythonic {

    namespace __builtin__ {

        namespace dict {

            template<class Iterable, class V=types::none_type>
                types::dict<typename std::remove_reference<Iterable>::type::value_type, V>
                fromkeys(Iterable && iter, V const & v = __builtin__::None);

            PROXY_DECL(pythonic::__builtin__::dict, fromkeys);

        }

    }

}

#endif

