#ifndef PYTHONIC_SET_UPDATE_HPP
#define PYTHONIC_SET_UPDATE_HPP

#include "pythonic/__dispatch__/update.hpp"

namespace pythonic {

    namespace __set__ {
        ALIAS(update, pythonic::__dispatch__::update);
        PROXY(pythonic::__set__, update);
    }
}

#endif


