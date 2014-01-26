#ifndef PYTHONIC_NUMPY_FINFO_HPP
#define PYTHONIC_NUMPY_FINFO_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/numpy_type.hpp"
#include "pythonic/types/finfo.hpp"

namespace pythonic {

    namespace numpy {
        template<class dtype=double>
            types::finfo<typename types::numpy_type<dtype>::type> finfo(dtype d=dtype()) {
                return types::finfo<typename types::numpy_type<dtype>::type>();
            }
        PROXY(pythonic::numpy, finfo)

    }

}

#endif

