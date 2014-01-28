#ifndef PYTHONIC_NUMPY_INSERT_HPP
#define PYTHONIC_NUMPY_INSERT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/traits.hpp"
#include "pythonic/__builtin__/None.hpp"

#include <algorithm>

namespace pythonic {

    namespace numpy {

        template<class T, size_t N, class I, class F>
            typename std::enable_if<types::is_iterable<I>::value and types::is_iterable<F>::value, types::ndarray<T,1>>::type
            insert(types::ndarray<T,N> const& in, I const& indices, F const& data, types::none_type axis=__builtin__::None)
            {
                types::ndarray<T,1> out(types::make_tuple(long(in.size()+std::min(indices.size(), data.size()))), __builtin__::None);
                auto out_iter = out.buffer;
                auto in_iter = in.buffer;
                auto data_iter = data.begin();
                for(long index : indices) {
                    out_iter = std::copy(in_iter, in.buffer + index, out_iter);
                    *out_iter++ = *data_iter++;
                    in_iter = in.buffer + index;
                }
                std::copy(in_iter, in.buffer + in.size(), out_iter);
                return out;
            }
        template<class T, size_t N, class I, class F>
            typename std::enable_if<types::is_iterable<I>::value and not types::is_iterable<F>::value, types::ndarray<T,1>>::type
            insert(types::ndarray<T,N> const& in, I const& indices, F const& data, types::none_type axis=__builtin__::None)
            {
                return insert(in, indices, types::list<F>({data}), axis);
            }
        template<class T, size_t N, class I, class F>
            typename std::enable_if<not types::is_iterable<I>::value and types::is_iterable<F>::value, types::ndarray<T,1>>::type
            insert(types::ndarray<T,N> const& in, I const& indices, F const& data, types::none_type axis=__builtin__::None)
            {
                return insert(in, types::list<I>({indices}), {data}, axis);
            }
        template<class T, size_t N, class I, class F>
            typename std::enable_if<not types::is_iterable<I>::value and not types::is_iterable<F>::value, types::ndarray<T,1>>::type
            insert(types::ndarray<T,N> const& in, I const& indices, F const& data, types::none_type axis=__builtin__::None)
            {
                return insert(in, types::list<I>({indices}), types::list<F>({data}), axis);
            }

        PROXY(pythonic::numpy, insert);

    }

}

#endif

