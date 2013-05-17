#ifndef PYTHONIC_MODULE_FINFO_H
#define PYTHONIC_MODULE_FINFO_H

namespace pythonic {
    namespace __finfo__ {

        template<class T>
            T eps(core::finfo<T> const&) {
                return std::numeric_limits<T>::epsilon();
            }
        PROXY(pythonic::__finfo__, eps);
    }
}
#endif
