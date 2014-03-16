#ifndef PYTHONIC_NUMPY_ARGMAX_HPP
#define PYTHONIC_NUMPY_ARGMAX_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/asarray.hpp"
#include "pythonic/__builtin__/ValueError.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            long argmax(E&& expr) {
                auto arr = asarray(expr);
                long sz = arr.size();
                if(not sz) 
                    throw types::ValueError("empty sequence");
                return std::max_element(arr.fbegin(), arr.fend()) - arr.fbegin();
            }
        PROXY(pythonic::numpy, argmax);


    }

}

#endif

