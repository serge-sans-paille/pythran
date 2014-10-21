#ifndef PYTHONIC_LIST_POP_HPP
#define PYTHONIC_LIST_POP_HPP

#include "pythonic/__dispatch__/pop.hpp"

namespace pythonic { namespace __builtin__  {

    namespace list {
        ALIAS(pop, pythonic::__dispatch__::pop);
        PROXY(pythonic::__builtin__::list, pop);
    }
}

}
#endif
