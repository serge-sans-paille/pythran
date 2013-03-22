#ifndef PYTHONIC_MODULE_MATH_H
#define PYTHONIC_MODULE_MATH_H

#include "nt2/toolbox/trigonometric/trigonometric.hpp"

namespace pythonic {
    namespace math {
        using std::acos;
        using nt2::cos;
        using std::exp;
        using std::sin;
        using std::sqrt;
        using std::log10;
        using std::isnan;
        using std::ceil;
        using std::floor;
        using std::fabs;
        using std::fmod;
        using std::ldexp;
        using std::tan;
        using std::asin;
        using std::atan;
        using std::atan2;
        using std::cosh;
        using std::sinh;
        using std::tanh;
        using std::atanh;
        using std::asinh;
        using std::acosh;
        using std::erf;
        using std::erfc;
        using std::log1p;
        using std::expm1;
        using std::lgamma;
        using std::trunc;
        using std::copysign;
        using std::hypot;
        using std::log;
        using std::isinf;
        using std::pow;
        long pow(long n, long m) { return std::pow(n,m); }

        double const pi = std::atan(1)*4;
        double const e = std::exp(1);

        std::tuple<double,long> frexp(double x)
        {
            int exp;
            double sig = std::frexp(x,&exp);
            return std::tuple<double,long>(sig,exp);
        }

        WRAP(double,gamma,std::tgamma,double);

        template<class T>
            T factorial(T x)
            {
                T res = 1;
                for(T i=2;i<=x;i++)
                    res *= i;
                return res;
            }

        std::tuple<double,double> modf(double x)
        {
            double i;
            double frac = std::modf(x,&i);
            return std::make_tuple(frac,i);
        }

        double log(double x, double base) { return log(x)/log(base); }

        template<class T>
            double degrees(T x) { return (x * 360.) / (2. * pi); }

        template<class T>
            double radians(T x) { return (x * 2. * pi) / 360.; }

        PROXY(pythonic::math,isinf);
        PROXY(pythonic::math,modf);
        PROXY(pythonic::math,frexp);
        PROXY(pythonic::math,factorial);
        PROXY(pythonic::math,trunc);
        PROXY(pythonic::math,gamma);
        PROXY(pythonic::math,lgamma);
        PROXY(pythonic::math,erf);
        PROXY(pythonic::math,erfc);
        PROXY(pythonic::math,degrees);
        PROXY(pythonic::math,radians);
        PROXY(pythonic::math,atanh);
        PROXY(pythonic::math,asinh);
        PROXY(pythonic::math,acosh);
        PROXY(pythonic::math,hypot);
        PROXY(pythonic::math,tanh);
        PROXY(pythonic::math,cosh);
        PROXY(pythonic::math,sinh);
        PROXY(pythonic::math,atan);
        PROXY(pythonic::math,atan2);
        PROXY(pythonic::math,asin);
        PROXY(pythonic::math,tan);
        PROXY(pythonic::math,log);
        PROXY(pythonic::math,log1p);
        PROXY(pythonic::math,expm1);
        PROXY(pythonic::math,ldexp);
        PROXY(pythonic::math,fmod);
        PROXY(pythonic::math,fabs);
        PROXY(pythonic::math,copysign);
        PROXY(pythonic::math,acos);
        PROXY(pythonic::math,cos);
        PROXY(pythonic::math,exp);
        PROXY(pythonic::math,sin);
        PROXY(pythonic::math,sqrt);
        PROXY(pythonic::math,log10);
        PROXY(pythonic::math,isnan);
        PROXY(pythonic::math,ceil);
        PROXY(pythonic::math,floor);
        PROXY(pythonic::math,pow);
    }
}

#endif
