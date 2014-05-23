#ifndef PYTHONIC_NDARRAY_FLATTEN_HPP
#define PYTHONIC_NDARRAY_FLATTEN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace __ndarray__ {
        template<class T, size_t N>
            types::ndarray<T, 1>
            flatten(types::ndarray<T,N> const& a) {
                return types::ndarray<T, 1>(a.mem, {a.size()});
            }

        PROXY(pythonic::__ndarray__, flatten);

    }

}

#endif

