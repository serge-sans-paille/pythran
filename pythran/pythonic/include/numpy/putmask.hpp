#ifndef PYTHONIC_INCLUDE_NUMPY_PUTMASK_HPP
#define PYTHONIC_INCLUDE_NUMPY_PUTMASK_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/asarray.hpp"
#include "pythonic/__builtin__/None.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N, class E,class F>
            types::none_type putmask(types::ndarray<T,N> & expr, E const& mask, F const& values);

        template<class E, class M, class F>
            types::none_type putmask(E & , M const& , F const& );

        PROXY_DECL(pythonic::numpy, putmask);

    }

}

#endif
