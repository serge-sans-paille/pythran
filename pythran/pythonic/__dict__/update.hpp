#ifndef PYTHONIC_DICT_UPDATE_HPP
#define PYTHONIC_DICT_UPDATE_HPP

#include "pythonic/__dispatch__/update.hpp"

namespace pythonic {

    namespace __dict__ {
        ALIAS(update, pythonic::__dispatch__::update);
        PROXY(pythonic::__dict__, update);
    }
}

#endif

