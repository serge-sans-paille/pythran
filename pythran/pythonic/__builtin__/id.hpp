#ifndef PYTHONIC_BUILTIN_ID_HPP
#define PYTHONIC_BUILTIN_ID_HPP

#include <cstdint>
#include "pythonic/types/long.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __builtin__ {

        template <class T>
            intptr_t id(T const & t) {
                return t.id();
            }

        intptr_t id(pythran_long_t const &t) {
            return reinterpret_cast<intptr_t>(&t);
        }
        intptr_t id(long const &t) {
            return reinterpret_cast<intptr_t>(&t);
        }
        intptr_t id(double const &t) {
            return reinterpret_cast<intptr_t>(&t);
        }
        intptr_t id(bool const &t) {
            return reinterpret_cast<intptr_t>(&t);
        }
        PROXY(pythonic::__builtin__,id);

    }

}

#endif

