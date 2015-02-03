#ifndef PYTHONIC_NDARRAY_FILL_HPP
#define PYTHONIC_NDARRAY_FILL_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/None.hpp"

namespace pythonic { namespace numpy  {

    namespace ndarray {
        template<class E, class F>
            types::none_type fill(E&& e, F f) {
              std::fill(e.begin(), e.end(), f);
              return __builtin__::None;
            }
        template<class T, size_t N, class F>
            types::none_type fill(types::ndarray<T, N>& e, F f) {
              std::fill(e.fbegin(), e.fend(), f);
              return __builtin__::None;
            }

        PROXY(pythonic::numpy::ndarray, fill);

    }

}

}
#endif

