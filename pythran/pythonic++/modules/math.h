#ifndef PYTHONIC_MODULE_MATH_H
#define PYTHONIC_MODULE_MATH_H

#include <gmpxx.h>

namespace pythonic {
    namespace math {
        using std::acos;
        using std::cos;
        using std::exp;
        using std::sin;
        using std::sqrt;
        using std::log10;
        using std::isnan;
        using std::ceil;
        using std::floor;
        using std::fabs;
        //using std::fmod;
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
        //using std::copysign;
        //using std::hypot;
        using std::log;
        using std::isinf;
        //using std::pow;
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

        /* Defines the function dealing with python long ints,
         simply by converting that long int to a double first.

         This is how python.math deals with a long int argument in most
         of the cases */
        #define MATH_MPZ_FLOAT(func) \
        auto func(const mpz_class &mpz) -> decltype(func(1.0)) { \
            return func(mpz.get_d()); \
        }

        /* Proxies the function, but adds the one dealing with bigints first */
        #define PROXY_MPZ(module, func) \
            MATH_MPZ_FLOAT(func) \
            PROXY(module, func)

        const mpz_class& trunc (const mpz_class &val) {
            return val;
        }

        template <typename T>
        inline T to_float (T val) {
            return val;
        };

        double to_float (const mpz_class &val) {
            return val.get_d();
        };

        template <typename T>
        inline T to_int (T val) {
            return val;
        };

        long to_int (const mpz_class &val) {
            return val.get_si();
        };

        template<typename T, typename U>
        double hypot(T x, U y) {
            return std::sqrt(to_float(x*x) + to_float(y*y));
        }

        template<typename T, typename U>
        double atan2(T x, T y) {
            return std::atan2(to_float(x),to_float(y));
        }

        template<typename T, typename U>
        double ldexp(T x, U y) {
            return std::ldexp(to_float(x), to_int(y));
        }

        template<typename T, typename U>
        double fmod(T x, U y) {
            return std::fmod(to_float(x), to_float(y));
        }

        template<typename T, typename U>
        T copysign(T x, U y) {
            return x * std::copysign(1, to_float(y));
        }

        template<typename T, typename U>
        double pow(T x, U y) {
            return std::pow(to_float(x), to_float(y));
        }

        PROXY_MPZ(pythonic::math,isinf);
        PROXY_MPZ(pythonic::math,modf);
        PROXY_MPZ(pythonic::math,frexp);
        PROXY(pythonic::math,factorial);//already templated
        PROXY(pythonic::math,trunc);//special impl for mpz
        PROXY_MPZ(pythonic::math,gamma);
        PROXY_MPZ(pythonic::math,lgamma);
        PROXY_MPZ(pythonic::math,erf);
        PROXY_MPZ(pythonic::math,erfc);
        PROXY_MPZ(pythonic::math,degrees);
        PROXY_MPZ(pythonic::math,radians);
        PROXY_MPZ(pythonic::math,atanh);
        PROXY_MPZ(pythonic::math,asinh);
        PROXY_MPZ(pythonic::math,acosh);
        PROXY(pythonic::math,hypot);//two args
        PROXY_MPZ(pythonic::math,tanh);
        PROXY_MPZ(pythonic::math,cosh);
        PROXY_MPZ(pythonic::math,sinh);
        PROXY_MPZ(pythonic::math,atan);
        PROXY(pythonic::math,atan2);//two args
        PROXY_MPZ(pythonic::math,asin);
        PROXY_MPZ(pythonic::math,tan);
        PROXY_MPZ(pythonic::math,log);
        PROXY_MPZ(pythonic::math,log1p);
        PROXY_MPZ(pythonic::math,expm1);
        PROXY(pythonic::math,ldexp);//two args
        PROXY(pythonic::math,fmod);//two args
        PROXY_MPZ(pythonic::math,fabs);
        PROXY(pythonic::math,copysign);//two args
        PROXY_MPZ(pythonic::math,acos);
        PROXY_MPZ(pythonic::math,cos);
        PROXY_MPZ(pythonic::math,exp);
        PROXY_MPZ(pythonic::math,sin);
        PROXY_MPZ(pythonic::math,sqrt);
        PROXY_MPZ(pythonic::math,log10);
        PROXY_MPZ(pythonic::math,isnan);
        PROXY_MPZ(pythonic::math,ceil);
        PROXY_MPZ(pythonic::math,floor);
        PROXY(pythonic::math,pow);//two args

        #undef PROXY_MPZ
        #undef MATH_MPZ_FLOAT
    }
}

#endif
