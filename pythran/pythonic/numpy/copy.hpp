#ifndef PYTHONIC_NUMPY_COPY_HPP
#define PYTHONIC_NUMPY_COPY_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        // list case
        template<class E>
            typename std::enable_if<!types::is_array<E>::value and !std::is_scalar<E>::value and !types::is_complex<E>::value,
                                    typename types::numpy_expr_to_ndarray<E>::type
                                    >::type
            copy(E const& v)
            {
                return typename types::numpy_expr_to_ndarray<E>::type{v};
            }

        // scalar / complex case
        template<class E>
            auto copy(E const &v) -> typename std::enable_if<std::is_scalar<E>::value or types::is_complex<E>::value, E>::type
            {
              return v;
            }


        // No copy is required for numpy_expr
        template<class E>
            auto copy(E && v) -> typename std::enable_if<types::is_array<E>::value, decltype(std::forward<E>(v))>::type
            {
                return std::forward<E>(v);
            }

        // ndarray case
        template<class T, size_t N>
            types::ndarray<T,N> copy(types::ndarray<T,N> const& a) {
                return a.copy();
            }
        PROXY(pythonic::numpy, copy);
    }
}

#endif

