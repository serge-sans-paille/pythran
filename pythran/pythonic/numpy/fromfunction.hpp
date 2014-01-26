#ifndef PYTHONIC_NUMPY_FROMFUNCTION_HPP
#define PYTHONIC_NUMPY_FROMFUNCTION_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/None.hpp"

namespace pythonic {

    namespace numpy {
        template<class F, size_t N, class dtype>
            struct fromfunction_helper;

        template<class F, class dtype>
            struct fromfunction_helper<F,1,dtype> {
                types::ndarray<typename std::remove_cv<typename std::remove_reference<decltype(std::declval<F>()(dtype()))>::type>::type, 1>
                    operator()(F&& f, types::array<long,1> const& shape, dtype d = dtype()) {
                        types::ndarray<typename std::remove_cv<typename std::remove_reference<decltype(f(dtype()))>::type>::type, 1> out(shape, __builtin__::None);
                        for(dtype i=0, n= out.shape[0]; i<n; ++i)
                            out[i] = f(i);
                        return out;
                    }
            };

        template<class F, class dtype>
            struct fromfunction_helper<F,2,dtype> {
                types::ndarray<typename std::remove_cv<typename std::remove_reference<decltype(std::declval<F>()(dtype(), dtype()))>::type>::type, 2>
                    operator()(F&& f, types::array<long,2> const& shape, dtype d = dtype()) {
                        types::ndarray<typename std::remove_cv<typename std::remove_reference<decltype(f(dtype(), dtype()))>::type>::type, 2> out(shape, __builtin__::None);
                        for(dtype i=0, n= out.shape[0]; i<n; ++i)
                            for(dtype j=0, m= out.shape[1]; j<m; ++j)
                                out[i][j] = f(i,j);
                        return out;
                    }
            };


        template<class F, size_t N, class dtype=double>
            auto fromfunction(F&& f, types::array<long, N> const& shape, dtype d = dtype())
            -> decltype(fromfunction_helper<F, N, dtype>()(std::forward<F>(f), shape)) {
                return fromfunction_helper<F, N, dtype>()(std::forward<F>(f), shape);
            }

        /* must specialize for higher order */
        PROXY(pythonic::numpy, fromfunction);


    }

}

#endif

