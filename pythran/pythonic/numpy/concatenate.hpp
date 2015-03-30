#ifndef PYTHONIC_NUMPY_CONCATENATE_HPP
#define PYTHONIC_NUMPY_CONCATENATE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/sum.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N, size_t M>
            types::ndarray<T,N> concatenate(types::array<types::ndarray<T,N>, M> const & ai) {
                long n = 0;
                long shape[N];
                shape[0] = 0L;
                for(auto const& a : ai) {
                    shape[0] += a.shape[0];
                    n += a.flat_size();
                }
                std::copy(ai[0].shape.begin() +1 , ai[0].shape.end(), &shape[1]);

                T* buffer = (T*)malloc(sizeof(T) * n);
                T* iter = buffer;
                for(auto const& a : ai) {
                    iter = std::copy(a.fbegin(), a.fend(), iter);
                }

                return types::ndarray<T,N>(buffer, shape);
            }

        namespace details {

            template<class ...Types>
                void concatenate(std::tuple<Types...> const& a, typename assignable<typename __combined<Types...>::type>::type::dtype* iter, utils::int_<1>)
                {
                    typename types::numpy_expr_to_ndarray<typename std::tuple_element<sizeof...(Types) - 1, std::tuple<Types...>>::type>::type t = std::get<sizeof...(Types) - 1>(a); // We force evaluation of the ndarray
                    std::copy(t.fbegin(), t.fend(), iter);
                }

            template<size_t M, class ...Types>
                void concatenate(std::tuple<Types...> const& a, typename assignable<typename __combined<Types...>::type>::type::dtype* iter, utils::int_<M>)
                {
                    typename types::numpy_expr_to_ndarray<typename std::tuple_element<sizeof...(Types) - M, std::tuple<Types...>>::type>::type t = std::get<sizeof...(Types) - M>(a); // We force evaluation of the ndarray
                    iter = std::copy(t.fbegin(), t.fend(), iter);
                    concatenate(a, iter, utils::int_<M-1>());
                }

            template<size_t N>
                long first_dim(types::array<long, N> const& fake_shape)
                {
                    // FIXME This is a hack to force list.fake_shape evaluation to types::array
                    return fake_shape[0];
                }

            template<class... Types, int... I>
                size_t concatenate_size(std::tuple<Types...> const& args, utils::seq<I...>)
                {
                    return __builtin__::sum(std::make_tuple(first_dim<std::tuple_element<0, std::tuple<Types...>>::type::value>(std::get<I-1>(args).shape)...));
                }

        }

        template<class... Types>
            typename assignable<typename __combined<Types...>::type>::type
            concatenate(std::tuple<Types...> const& args) {

                using return_type = typename assignable<typename __combined<Types...>::type>::type;
                using T = typename return_type::dtype;

                types::array<long, return_type::value> shape = std::get<0>(args).shape;
                size_t n = shape[0];
                shape[0] = details::concatenate_size(args, typename utils::gens<1+sizeof...(Types)>::type{});
                n = size_t(std::get<0>(args).flat_size() * shape[0] / double(n));

                T* buffer = (T*)malloc(sizeof(T) * n);
                details::concatenate(args, buffer, utils::int_<sizeof...(Types)>());

                return types::ndarray<T,return_type::value>(buffer, shape);
            }

        PROXY(pythonic::numpy, concatenate);

    }

}

#endif
