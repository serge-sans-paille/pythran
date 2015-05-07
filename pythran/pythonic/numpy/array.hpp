#ifndef PYTHONIC_NUMPY_ARRAY_HPP
#define PYTHONIC_NUMPY_ARRAY_HPP

#include "pythonic/include/numpy/array.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/nested_container.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_type.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, class dtype>
            types::ndarray<typename types::numpy_type<dtype>::type, utils::nested_container_depth<typename std::remove_cv<typename std::remove_reference<T>::type>::type>::value > array(T&& iterable, dtype d)
            {
                return {std::forward<T>(iterable)};
            }

        PROXY_IMPL(pythonic::numpy, array);

    }

}

#endif
