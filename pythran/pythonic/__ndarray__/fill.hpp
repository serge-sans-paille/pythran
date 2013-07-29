#ifndef PYTHONIC_NDARRAY_FILL_HPP
#define PYTHONIC_NDARRAY_FILL_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/None.hpp"

namespace pythonic {

    namespace __ndarray__ {
        template<class E, class F>
            types::none_type fill(E&& e, F f) {
                std::fill(e.buffer, e.buffer + e.size(), f);
                return __builtin__::None;
            }

        PROXY(pythonic::__ndarray__, fill);

    }

}

#endif

