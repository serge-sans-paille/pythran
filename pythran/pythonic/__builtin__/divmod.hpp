#ifndef PYTHONIC_BUILTIN_DIVMOD_HPP
#define PYTHONIC_BUILTIN_DIVMOD_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/tuple.hpp"

namespace pythonic {

    namespace __builtin__ {
        template<class T0, class T1>
            auto divmod(T0 const& t0, T1 const& t1) // other types are left over
            -> decltype(types::make_tuple(t0/t1, t0%t1)) {
                return types::make_tuple(t0/t1, t0%t1);
            }
        PROXY(pythonic::__builtin__, divmod);

    }

}

#endif

