#ifndef PYTHONIC_STR_COUNT_HPP
#define PYTHONIC_STR_COUNT_HPP

#include "pythonic/__dispatch__/count.hpp"

namespace pythonic { namespace __builtin__  {

    namespace str {
        ALIAS(count, pythonic::__dispatch__::count);
        PROXY(pythonic::__builtin__::str, count);
    }
}

}
#endif

