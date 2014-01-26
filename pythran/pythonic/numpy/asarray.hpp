#ifndef PYTHONIC_NUMPY_ASARRAY_HPP
#define PYTHONIC_NUMPY_ASARRAY_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/array.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            struct _asarray {
                template<class... Types>
                    auto operator()(Types&&... args) -> decltype(array(std::forward<Types>(args)...)) {
                        return array(std::forward<Types>(args)...);
                    }
            };
        template<class T, size_t N>
            struct _asarray<types::ndarray<T,N>> {
                template<class F>
                    types::ndarray<T,N> operator()(F&& a) {
                        return a;
                    }
            };

        template<class E, class... Types>
            auto asarray(E&& e, Types&&... args) -> decltype(_asarray<typename std::remove_cv<typename std::remove_reference<E>::type>::type>()(std::forward<E>(e), std::forward<Types>(args)...)) {
                return _asarray<typename std::remove_cv<typename std::remove_reference<E>::type>::type>()(std::forward<E>(e), std::forward<Types>(args)...);
            }

        PROXY(pythonic::numpy, asarray);

    }

}

#endif

