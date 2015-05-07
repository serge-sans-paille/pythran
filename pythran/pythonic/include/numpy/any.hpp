#ifndef PYTHONIC_INCLUDE_NUMPY_ANY_HPP
#define PYTHONIC_INCLUDE_NUMPY_ANY_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/ValueError.hpp"
#include "pythonic/numpy/add.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            bool _any(E begin, E end, utils::int_<1>);

        template<class E, size_t N>
            bool _any(E begin, E end, utils::int_<N>);

        template<class E>
            bool
            any(E const& expr, types::none_type _ = types::none_type());

        template<class E>
            auto any(E const& array, long axis)
            -> typename std::enable_if<E::value == 1, decltype(any(array))>::type;

        template<class E>
            typename std::enable_if<E::value != 1, types::ndarray<typename E::dtype, E::value - 1>>::type
            any(E const& array, long axis);

        PROXY_DECL(pythonic::numpy, any);

    }

}

#endif
