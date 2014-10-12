#ifndef PYTHONIC_FILE_NEXT_HPP
#define PYTHONIC_FILE_NEXT_HPP

#include "pythonic/__dispatch__/next.hpp"

namespace pythonic { namespace __builtin__  {

    namespace file {
        ALIAS(next, pythonic::__dispatch__::next);
        PROXY(pythonic::__builtin__::file, next);
    }
}

}
#endif

