#ifndef PYTHONIC_COMPLEX_CONJUGATE_HPP
#define PYTHONIC_COMPLEX_CONJUGATE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/conjugate.hpp"

namespace pythonic {

    namespace __complex___ {
        template<class T>
            auto conjugate(T&& t)
            -> decltype(numpy::proxy::conjugate{}(std::forward<T>(t)))
            {
                return numpy::proxy::conjugate{}(std::forward<T>(t));
            }
        PROXY(pythonic::__complex___, conjugate);

    }

}

#endif

