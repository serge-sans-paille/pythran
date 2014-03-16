#ifndef PYTHONIC_NUMPY_ARGMIN_HPP
#define PYTHONIC_NUMPY_ARGMIN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/asarray.hpp"
#include "pythonic/__builtin__/ValueError.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            long argmin(E&& expr) {
                auto arr = asarray(expr);
                long sz = arr.size();
                if(not sz) 
                    throw types::ValueError("empty sequence");
                return std::min_element(arr.fbegin(), arr.fend()) - arr.fbegin();
            }
        PROXY(pythonic::numpy, argmin);

    }

}

#endif

