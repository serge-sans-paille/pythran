#ifndef PYTHONIC_NUMPY_APPEND_HPP
#define PYTHONIC_NUMPY_APPEND_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N, class F>
            types::ndarray<
            typename std::remove_cv<
            typename std::remove_reference<
            decltype(
                    std::declval<T>()
                    +
                    std::declval<typename utils::nested_container_value_type<F>::type>())
            >::type
            >::type,
            1> append(types::ndarray<T,N> const& nto, F const& data) {
                typename types::numpy_expr_to_ndarray<F>::type ndata(data);
                long nsize = nto.size() + ndata.size();
                types::ndarray<
                    typename std::remove_cv<
                    typename std::remove_reference<
                    decltype(
                            std::declval<T>()
                            +
                            std::declval<typename utils::nested_container_value_type<F>::type>())
                    >::type
                    >::type,
                    1> out(types::make_tuple(nsize), __builtin__::None);
                size_t i=0;
                auto out_back = std::copy(nto.fbegin(), nto.fend(), out.fbegin());
                std::copy(ndata.fbegin(), ndata.fend(), out_back);
                return out;
            }
        template<class T, class F>
            types::ndarray<
            typename std::remove_cv<
            typename std::remove_reference<
            decltype(
                    std::declval<typename utils::nested_container_value_type<types::list<T>>::type>()
                    +
                    std::declval<typename utils::nested_container_value_type<F>::type>())
            >::type
            >::type,
            1> append(types::list<T> const& to, F const& data) {
                return append(typename types::numpy_expr_to_ndarray<types::list<T>>::type(to), data);
            }

        PROXY(pythonic::numpy, append);

    }

}

#endif

