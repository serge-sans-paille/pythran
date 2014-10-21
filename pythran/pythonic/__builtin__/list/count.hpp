#ifndef PYTHONIC_LIST_COUNT_HPP
#define PYTHONIC_LIST_COUNT_HPP

#include "pythonic/__dispatch__/count.hpp"

namespace pythonic { namespace __builtin__  {

    namespace list {
        ALIAS(count, pythonic::__dispatch__::count);
        PROXY(pythonic::__builtin__::list, count);
    }
}

}
#endif



