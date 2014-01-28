#ifndef PYTHONIC_NUMPY_DELETE_HPP
#define PYTHONIC_NUMPY_DELETE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N>
            types::ndarray<T,1> delete_(types::ndarray<T,N> const& a, long index, types::none_type axis=__builtin__::None) {
                types::ndarray<T,1> out(types::make_tuple(long(a.size())-1), __builtin__::None);
                long n = a.size();
                index = std::min(n, index);
                std::copy(a.buffer + index + 1 , a.buffer + n, std::copy(a.buffer, a.buffer + index, out.buffer));
                return out;
            }

        template<class T, size_t N, class I>
            typename std::enable_if<!std::is_scalar<I>::value, types::ndarray<T,1>>::type
            delete_(types::ndarray<T,N> const& in, I const& indices, types::none_type axis=__builtin__::None) {
                types::ndarray<T,1> out(types::make_tuple(long(in.size())-indices.size()), __builtin__::None);
                auto out_iter = out.buffer;
                auto in_iter = in.buffer;
                for(long index : indices) {
                    out_iter = std::copy(in_iter, in.buffer + index, out_iter);
                    in_iter = in.buffer + index + 1;
                }
                std::copy(in_iter, in.buffer + in.size(), out_iter);
                return out;
            }

        PROXY(pythonic::numpy, delete_);

    }

}

#endif

