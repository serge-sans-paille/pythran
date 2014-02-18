#ifndef PYTHONIC_TYPES_COMPLEX_HPP
#define PYTHONIC_TYPES_COMPLEX_HPP

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

#define GET_COMPLEX(T)\
    template <int I>\
T& getattr( std::complex<T>& t) {return reinterpret_cast<T*>(&t)[I]; }\
\
template <int I>\
T getattr( std::complex<T> const &t ) { return I == 0 ? std::real(t) :  std::imag(t); }

GET_COMPLEX(double)

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
