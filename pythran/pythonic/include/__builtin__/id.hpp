#ifndef PYTHONIC_INCLUDE_BUILTIN_ID_HPP
#define PYTHONIC_INCLUDE_BUILTIN_ID_HPP

#include <cstdint>
#include "pythonic/types/long.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __builtin__ {

        template <class T>
            intptr_t id(T const & t);

        intptr_t id(pythran_long_t const &t);
        intptr_t id(long const &t);
        intptr_t id(double const &t);
        intptr_t id(bool const &t);

        PROXY_DECL(pythonic::__builtin__, id);

    }

}

#endif


