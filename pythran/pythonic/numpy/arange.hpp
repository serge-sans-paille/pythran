#ifndef PYTHONIC_NUMPY_ARANGE_HPP
#define PYTHONIC_NUMPY_ARANGE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/numpy_type.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, class U, class S=long, class dtype=decltype(std::declval<T>()+std::declval<U>()+std::declval<S>())>
            types::ndarray<typename types::numpy_type<dtype>::type, 1> arange(T begin, U end, S step=S(1), dtype d=dtype())
            {
                typedef typename types::numpy_type<dtype>::type R;
                size_t size = std::max(R(0), R(std::ceil((end - begin)/step)));
                types::ndarray<R, 1> a(types::make_tuple((long)size), __builtin__::None);
                if(size)
                {
                    auto prev = a.buffer,
                         end = a.buffer + a.size();
                    *prev = begin;
                    for(auto iter = prev + 1; iter!=end; ++iter) {
                        *iter = *prev + step;
                        prev = iter;
                    }
                }
                return a;
            }

        template<class T>
            types::ndarray<T, 1> arange(T end) {
                return arange(T(0), end);
            }
        PROXY(pythonic::numpy, arange);

    }

}

#endif

