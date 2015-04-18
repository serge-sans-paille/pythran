#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_UPDATE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_UPDATE_HPP

#include "pythonic/__dispatch__/update.hpp"

namespace pythonic {

    namespace __builtin__ {

        namespace dict {

            ALIAS_DECL(update, pythonic::__dispatch__::update);

            PROXY_DECL(pythonic::__builtin__::dict, update);
        }
    }
}

#endif
