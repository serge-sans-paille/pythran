
#ifndef PYTHONIC_COMPLEX_H
#define PYTHONIC_COMPLEX_H
namespace pythonic {
    namespace _complex_ { /* to avoid conflict with the complex intrinsic */
        template<class T>
            std::complex<T> conjugate(std::complex<T> const &c) {
                return std::conj(c);
            }
        PROXY(pythonic::_complex_, conjugate);
    }
}
#endif
