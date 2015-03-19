#ifndef PYTHONIC_SET_UPDATE_HPP
#define PYTHONIC_SET_UPDATE_HPP

#include "pythonic/include/__builtin__/set/update.hpp"

#include "pythonic/__dispatch__/update.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace set {

            ALIAS(update, pythonic::__dispatch__::update);

            PROXY_IMPL(pythonic::__builtin__::set, update);
        }
    }

}
#endif 
