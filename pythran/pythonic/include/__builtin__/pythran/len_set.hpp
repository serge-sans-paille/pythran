#ifndef PYTHONIC_INCLUDE_BUILTIN_PYTHRAN_LEN_SET_HPP
#define PYTHONIC_INCLUDE_BUILTIN_PYTHRAN_LEN_SET_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __builtin__ {

        namespace pythran {

            template <class Iterable>
                long len_set(Iterable const& s);

            PROXY_DECL(pythonic::__builtin__::pythran, len_set);
        }
    }
}

#endif
