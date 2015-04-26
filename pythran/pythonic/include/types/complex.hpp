#ifndef PYTHONIC_INCLUDE_TYPES_COMPLEX_HPP
#define PYTHONIC_INCLUDE_TYPES_COMPLEX_HPP

#include <complex>
#include <nt2/sdk/complex/complex.hpp>

namespace std {
    std::complex<double> operator+(std::complex<double> self, long other);
    std::complex<double> operator+(long self, std::complex<double> other);
    std::complex<double> operator-(std::complex<double> self, long other);
    std::complex<double> operator-(long self, std::complex<double> other);
    std::complex<double> operator*(std::complex<double> self, long other);
    std::complex<double> operator*(long self, std::complex<double> other);
    std::complex<double> operator/(std::complex<double> self, long other);
    std::complex<double> operator/(long self, std::complex<double> other);
}

namespace pythonic {
    namespace __builtin__ {
        template <size_t AttributeID>
            double getattr( std::complex<double> const &self);
    }
}

/* for type inference { */

#include "pythonic/types/combined.hpp"
template<class K>
struct __combined<indexable<K>, std::complex<double>> {
    using type = std::complex<double>;
};

template<class K>
struct __combined<std::complex<double>, indexable<K>> {
    using type = std::complex<double>;
};

/* } */

#endif
