#ifndef PYTHONIC_TYPES_COMPLEX_HPP
#define PYTHONIC_TYPES_COMPLEX_HPP

#include "pythonic/types/attr.hpp"
#include <complex>

namespace std {
    std::complex<double> operator+(std::complex<double> self, long other) {
        return self + double(other);
    }
    std::complex<double> operator+(long self, std::complex<double> other) {
        return double(self) + other;
    }
    std::complex<double> operator-(std::complex<double> self, long other) {
        return self - double(other);
    }
    std::complex<double> operator-(long self, std::complex<double> other) {
        return double(self) - other;
    }
    std::complex<double> operator*(std::complex<double> self, long other) {
        return self * double(other);
    }
    std::complex<double> operator*(long self, std::complex<double> other) {
        return double(self) * other;
    }
    std::complex<double> operator/(std::complex<double> self, long other) {
        return self / double(other);
    }
    std::complex<double> operator/(long self, std::complex<double> other) {
        return double(self) / other;
    }
}

namespace pythonic {
    namespace __builtin__ {
        template <size_t AttributeID>
            double getattr( std::complex<double> const &self) {
                return AttributeID == pythonic::types::attr::REAL ? std::real(self) : std::imag(self);
            }
    }
}

    /* for type inference { */

#include "pythonic/types/combined.hpp"
template<class K>
struct __combined<indexable<K>, std::complex<double>> {
    typedef std::complex<double> type;
};

template<class K>
struct __combined<std::complex<double>, indexable<K>> {
    typedef std::complex<double> type;
};

/* } */

#endif
