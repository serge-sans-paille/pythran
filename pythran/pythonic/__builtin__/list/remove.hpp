#ifndef PYTHONIC_LIST_REMOVE_HPP
#define PYTHONIC_LIST_REMOVE_HPP

#include "pythonic/__dispatch__/remove.hpp"

namespace pythonic { namespace __builtin__  {

    namespace list {
        ALIAS(remove, pythonic::__dispatch__::remove);
        PROXY(pythonic::__builtin__::list, remove);
    }
}

}
#endif


