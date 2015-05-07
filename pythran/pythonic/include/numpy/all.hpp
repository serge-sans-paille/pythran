#ifndef PYTHONIC_INCLUDE_NUMPY_ALL_HPP
#define PYTHONIC_INCLUDE_NUMPY_ALL_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/ValueError.hpp"
#include "pythonic/numpy/multiply.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            bool _all(E begin, E end, utils::int_<1>);

        template<class E, size_t N>
            bool _all(E begin, E end, utils::int_<N>);

        template<class E>
            bool
            all(E const& expr, types::none_type _ = types::none_type());

        template<class E>
            auto all(E const& array, long axis)
            -> typename std::enable_if<E::value == 1, decltype(all(array))>::type;

        template<class E>
            typename std::enable_if<E::value != 1, types::ndarray<typename E::dtype, E::value - 1>>::type
            all(E const& array, long axis);

        PROXY_DECL(pythonic::numpy, all);

    }

}

#endif
