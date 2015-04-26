#ifndef PYTHONIC_TYPES_COMPLEX_HPP
#define PYTHONIC_TYPES_COMPLEX_HPP

#include "pythonic/include/types/complex.hpp"

#include "pythonic/types/attr.hpp"

#include <complex>
#include <nt2/sdk/complex/complex.hpp>

namespace std {
    std::complex<double> operator+(std::complex<double> self, long other)
    {
        return self + double(other);
    }

    std::complex<double> operator+(long self, std::complex<double> other)
    {
        return double(self) + other;
    }

    std::complex<double> operator-(std::complex<double> self, long other)
    {
        return self - double(other);
    }

    std::complex<double> operator-(long self, std::complex<double> other)
    {
        return double(self) - other;
    }

    std::complex<double> operator*(std::complex<double> self, long other)
    {
        return self * double(other);
    }

    std::complex<double> operator*(long self, std::complex<double> other)
    {
        return double(self) * other;
    }

    std::complex<double> operator/(std::complex<double> self, long other)
    {
        return self / double(other);
    }

    std::complex<double> operator/(long self, std::complex<double> other)
    {
        return double(self) / other;
    }
}

namespace pythonic {

    namespace __builtin__ {

        template <size_t AttributeID>
            double getattr(std::complex<double> const &self)
            {
                return AttributeID == pythonic::types::attr::REAL ? std::real(self) : std::imag(self);
            }
    }
}

#endif
