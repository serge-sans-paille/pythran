#ifndef PYTHONIC_CORE_FINFO_H
#define PYTHONIC_CORE_FINFO_H

namespace pythonic {
    namespace core {
        template<class T>
            struct finfo {
                T eps() const {
                    return std::numeric_limits<T>::epsilon();
                }
            };
    }
}

#endif

