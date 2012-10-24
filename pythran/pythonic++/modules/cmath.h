#ifndef PYTHONIC_MODULE_CMATH_H
#define PYTHONIC_MODULE_CMATH_H

namespace pythonic {
    namespace cmath {
        using std::cos;
        using std::sin;
        using std::exp;
        using std::sqrt;
        using std::log10;
        using std::isnan;
        double const pi = std::atan(1)*4;
        double const e = std::exp(1);

        PROXY(pythonic::cmath,cos);
        PROXY(pythonic::cmath,sin);
        PROXY(pythonic::cmath,exp);
        PROXY(pythonic::cmath,sqrt);
        PROXY(pythonic::cmath,log10);
        PROXY(pythonic::cmath,isnan);
    }
}

#endif
