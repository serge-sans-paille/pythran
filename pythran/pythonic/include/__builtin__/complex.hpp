#ifndef PYTHONIC_INCLUDE_BUILTIN_COMPLEX_HPP
#define PYTHONIC_INCLUDE_BUILTIN_COMPLEX_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/complex.hpp"


namespace pythonic {

    namespace __builtin__ {

        template<class T0=double, class T1=double> // do not handle string as first argument
            std::complex<double> complex(T0 const& v0=T0(0), T1 const& v1 = T1(0));

        PROXY_DECL(pythonic::__builtin__, complex);

    }

}

#endif
