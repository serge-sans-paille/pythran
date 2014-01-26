#ifndef PYTHONIC_NUMPY_ARGMAX_HPP
#define PYTHONIC_NUMPY_ARGMAX_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            long argmax(E&& expr) {
                long sz = expr.size();
                if(not sz) 
                    throw types::ValueError("empty sequence");
                auto res = expr.at(0);
                long index = 0;
                for(long i = 1; i< sz ; ++i) {
                    auto e_i = expr.at(i);
                    if(e_i > res) {
                        res = e_i;
                        index = i;
                    }
                }
                return index;
            }
        PROXY(pythonic::numpy, argmax);


    }

}

#endif

