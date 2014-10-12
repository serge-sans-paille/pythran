#ifndef PYTHONIC_SET_REMOVE_HPP
#define PYTHONIC_SET_REMOVE_HPP

#include "pythonic/__dispatch__/remove.hpp"

namespace pythonic { namespace __builtin__  {

    namespace set {
        ALIAS(remove, pythonic::__dispatch__::remove);
        PROXY(pythonic::__builtin__::set, remove);
    }
}

}
#endif 

