#ifndef PYTHONIC_INCLUDE_NUMPY_ARGMIN_HPP
#define PYTHONIC_INCLUDE_NUMPY_ARGMIN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/asarray.hpp"
#include "pythonic/__builtin__/ValueError.hpp"

namespace pythonic {

    namespace numpy {
        template<class I0, class T>
            long _argmin(I0 begin, I0 end, T& min_elts, utils::int_<1>);

        template<class I0, size_t N, class T>
            long _argmin(I0 begin, I0 end, T& min_elts, utils::int_<N>);

        template<class E>
            long argmin(E const& expr);

        PROXY_DECL(pythonic::numpy, argmin);

    }
}

#endif
