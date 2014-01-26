#ifndef PYTHONIC_TYPES_FINFO_HPP
#define PYTHONIC_TYPES_FINFO_HPP

#include <limits>

namespace pythonic {

    namespace types {
        template<class T>
            struct finfo {
                T eps() const {
                    return std::numeric_limits<T>::epsilon();
                }
            };

    }
}
/* pythran attribute system { */
namespace pythonic {
    namespace types {
        namespace __finfo {

            template<int I, class T>
                struct getattr;
            template<class T>
                struct getattr<0,T> {
                    auto operator()(finfo<T> const& f) -> decltype(f.eps()) const {
                        return f.eps();
                    }
                };
        }
    }
}
template<int I, class T>
auto getattr(pythonic::types::finfo<T> const& f) -> decltype(pythonic::types::__finfo::getattr<I,T>()(f)) {
    return pythonic::types::__finfo::getattr<I,T>()(f);
}
/* } */
#endif
