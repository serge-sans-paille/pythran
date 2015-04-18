#ifndef PYTHONIC_BUILTIN_COMPLEX_HPP
#define PYTHONIC_BUILTIN_COMPLEX_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/complex.hpp"
#include "pythonic/include/__builtin__/complex.hpp"


namespace pythonic {

    namespace __builtin__ {

        template<class T0, class T1> // do not handle string as first argument
            std::complex<double> complex(T0 const& v0, T1 const& v1)
            {
                return std::complex<double>(v0,v1);
            }

        PROXY_IMPL(pythonic::__builtin__, complex);

    }

}

#endif
