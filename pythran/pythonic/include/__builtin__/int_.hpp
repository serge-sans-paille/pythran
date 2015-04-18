#ifndef PYTHONIC_INCLUDE_BUILTIN_INT_HPP
#define PYTHONIC_INCLUDE_BUILTIN_INT_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __builtin__ {

        template<class T>
            long int_(T&& t);

        long int_(char t);

        long int_();

        PROXY_DECL(pythonic::__builtin__, int_);

    }

}

#endif
