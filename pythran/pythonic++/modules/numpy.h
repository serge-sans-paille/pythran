#ifndef PYTHONIC_MODULE_NUMPY_H
#define PYTHONIC_MODULE_NUMPY_H

namespace pythonic {
    namespace numpy {
        core::ndarray<double,2> array() {
            core::ndarray<double,2> a({1,1});
            a(0,0) = 1;
            return a;
            }

        PROXY(pythonic::numpy, array);
    }
}

#endif
