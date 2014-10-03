#ifndef PYTHONIC_FILE_NEXT_HPP
#define PYTHONIC_FILE_NEXT_HPP

#include "pythonic/__dispatch__/next.hpp"

namespace pythonic {

    namespace __file__ {
        ALIAS(next, pythonic::__dispatch__::next);
        PROXY(pythonic::__file__, next);
    }
}

#endif

