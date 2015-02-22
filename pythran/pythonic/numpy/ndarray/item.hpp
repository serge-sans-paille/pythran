#ifndef PYTHONIC_NDARRAY_ITEM_HPP
#define PYTHONIC_NDARRAY_ITEM_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic { namespace numpy  {

    namespace ndarray {

        template<class T, size_t N>
            T item(types::ndarray<T, N> const& expr, long i)
            {
                if(i<0) i += expr.flat_size();
                return *(expr.fbegin() + i);
            }


        template<class E, size_t N>
            auto item(E&& expr, types::array<long, N> const& i) -> decltype(expr[i])
            {
                return expr[i];
            }
        // only for compatibility purpose, very bad impl
        template<class E>
            typename types::numpy_expr_to_ndarray<typename std::remove_reference<E>::type>::type::dtype
            item(E&& expr, long i)
            {
                if(i<0) i += expr.flat_size();
                return typename types::numpy_expr_to_ndarray<typename std::remove_reference<E>::type>::type{std::forward<E>(expr)}.flat()[i];
            }
        PROXY(pythonic::numpy::ndarray, item);

    }

}

}
#endif

