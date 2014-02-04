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
T& getattr( std::complex<T>& );\
template <>\
T& getattr<0>( std::complex<T>& t) { return reinterpret_cast<T*>(&t)[0]; }\
template <>\
T& getattr<1>( std::complex<T>& t) { return reinterpret_cast<T*>(&t)[1]; }\
\
template <int I>\
T const & getattr( std::complex<T> const & );\
template <>\
T const & getattr<0>( std::complex<T> const & t) { return reinterpret_cast<T const *>(&t)[0]; }\
template <>\
T const & getattr<1>( std::complex<T> const & t) { return reinterpret_cast<T const *>(&t)[1]; }\

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
