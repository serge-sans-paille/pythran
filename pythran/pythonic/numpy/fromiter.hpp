#ifndef PYTHONIC_NUMPY_FROMITER_HPP
#define PYTHONIC_NUMPY_FROMITER_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class Iterable, class dtype=double>
            types::ndarray<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type::value_type, 1>
            fromiter(Iterable&& iterable, dtype d=dtype(), long count = -1)
            {
                typedef typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type::value_type T;
                if(count < 0) {
                    types::list<T> buffer(0);
                    std::copy(iterable.begin(), iterable.end(), std::back_inserter(buffer));
                    return types::ndarray<T,1>(buffer);
                }
                else {
                    T* buffer = new T[count];
                    std::copy_n(iterable.begin(), count, buffer);
                    long shape [1] = { count };
                    return types::ndarray<T,1>(buffer, shape);
                }
            }
        PROXY(pythonic::numpy, fromiter);

    }

}

#endif

