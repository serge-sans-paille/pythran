#ifndef PYTHONIC_INCLUDE_NUMPY_NANARGMIN_HPP
#define PYTHONIC_INCLUDE_NUMPY_NANARGMIN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/ValueError.hpp"
#include "pythonic/numpy/isnan.hpp"

namespace pythonic {

    namespace numpy {
        template<class E, class F>
            void _nanargmin(E begin, E end, F& min, long& index, long& where,utils::int_<1>);

        template<class E, class F, size_t N>
            void _nanargmin(E begin, E end, F& min, long& index, long& where, utils::int_<N>);

        template<class E>
            typename types::numpy_expr_to_ndarray<E>::T
            nanargmin(E const& expr);

        PROXY_DECL(pythonic::numpy, nanargmin);

    }

}

#endif
