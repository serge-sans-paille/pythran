#ifndef PYTHONIC_NUMPY_CONCATENATE_HPP
#define PYTHONIC_NUMPY_CONCATENATE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N, size_t M>
            types::ndarray<T,N> concatenate(types::array<types::ndarray<T,N>, M> const & ai) {
                long n = 0;
                long shape[N];
                shape[0] = 0L;
                for(auto const& a : ai) {
                    shape[0] += a.shape[0];
                    n += a.size();
                }
                std::copy(ai[0].shape.begin() +1 , ai[0].shape.end(), &shape[1]);

                T* buffer = (T*)malloc(sizeof(T) * n);
                T* iter = buffer;
                for(auto const& a : ai) {
                    iter = std::copy(a.fbegin(), a.fend(), iter);
                }

                return types::ndarray<T,N>(buffer, shape);
            }

        template<class T, size_t N, class A>
            void _concatenate_helper(types::array<T, N>& a, A const& t, utils::int_<1>) {
                a[N - 1] = std::get<N-1>(t);
            }
        template<class T, size_t N, class A, size_t M>
            void _concatenate_helper(types::array<T, N>& a, A const& t, utils::int_<M>) {
                a[N - M] = std::get<N-M>(t);
                _concatenate_helper(a, t, utils::int_<M-1>());
            }
        template<class... Types>
            typename assignable<typename __combined<Types...>::type>::type
            concatenate(std::tuple<Types...> const& args) {
                types::array<typename assignable<typename __combined<Types...>::type>::type, sizeof...(Types)> params;
                _concatenate_helper(params, args, utils::int_<sizeof...(Types)>());
                return concatenate(params);
            }
        PROXY(pythonic::numpy, concatenate);

    }

}

#endif

