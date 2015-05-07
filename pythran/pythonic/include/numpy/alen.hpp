#ifndef PYTHONIC_INCLUDE_NUMPY_ALEN_HPP
#define PYTHONIC_INCLUDE_NUMPY_ALEN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T>
            long alen(T&& expr);

        PROXY_DECL(pythonic::numpy, alen);

    }

}

#endif
