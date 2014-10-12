#ifndef PYTHONIC_SET_COPY_HPP
#define PYTHONIC_SET_COPY_HPP

#include "pythonic/__dispatch__/copy.hpp"

namespace pythonic { namespace __builtin__  {

    namespace set {
        ALIAS(copy, pythonic::__dispatch__::copy);
        PROXY(pythonic::__builtin__::set, copy);
    }
}

}
#endif 


