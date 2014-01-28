#ifndef PYTHONIC_NUMPY_FLIPLR_HPP
#define PYTHONIC_NUMPY_FLIPLR_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N>
            types::ndarray<T,N> fliplr(types::ndarray<T,N> const& a) {
                static_assert(N>=2, "fliplr only works on array of dimension >= 2");
                types::ndarray<T,N> out(a.shape, __builtin__::None);
                std::copy(a.buffer, a.buffer + a.size(), out.buffer);
                for(auto col : out)
                    std::reverse(col.begin(), col.end());
                return out;
            }

        PROXY(pythonic::numpy, fliplr); // does not return a view...

    }

}

#endif

