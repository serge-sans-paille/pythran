#ifndef PYTHONIC_MODULE_MATH_H
#define PYTHONIC_MODULE_MATH_H

#include <nt2/include/functions/acos.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/log10.hpp>
#include <nt2/include/functions/log2.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/ceil.hpp>
#include <nt2/include/functions/floor.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/mod.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/tan.hpp>
#include <nt2/include/functions/asin.hpp>
#include <nt2/include/functions/atan.hpp>
#include <nt2/include/functions/atan2.hpp>
#include <nt2/include/functions/cosh.hpp>
#include <nt2/include/functions/sinh.hpp>
#include <nt2/include/functions/tanh.hpp>
#include <nt2/include/functions/atanh.hpp>
#include <nt2/include/functions/asinh.hpp>
#include <nt2/include/functions/acosh.hpp>
#include <nt2/include/functions/erf.hpp>
#include <nt2/include/functions/erfc.hpp>
#include <nt2/include/functions/log1p.hpp>
#include <nt2/include/functions/expm1.hpp>
#include <nt2/include/functions/gamma.hpp>
#include <nt2/toolbox/boost_math/functions/lgamma.hpp>
#include <nt2/toolbox/boost_math/functions/tgamma.hpp>
#include <nt2/include/functions/trunc.hpp>
#include <nt2/include/functions/copysign.hpp>
#include <nt2/include/functions/hypot.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/pow.hpp>

namespace pythonic {
    namespace math {
        using nt2::acos;
        using nt2::cos;
        using nt2::exp;
        using nt2::sin;
        using nt2::sqrt;
        using nt2::log10;
        using nt2::log2;
        ALIAS(nt2::is_nan, isnan);
        using nt2::ceil;
        using nt2::floor;
        ALIAS(nt2::abs, fabs);

        /* add a cast in the wrapper to make sure the right type is used */
        template<typename T0, typename T1>
        auto fmod(T0 arg0, T1 arg1) ->  decltype(nt2::mod((decltype(std::declval<T0>() + std::declval<T1>()))arg0, (decltype(std::declval<T0>() + std::declval<T1>()))arg1)) {
            typedef decltype(std::declval<T0>() + std::declval<T1>()) common_type;
            return nt2::mod((common_type)arg0, (common_type)arg1);
        }

        using nt2::ldexp;
        using nt2::tan;
        using nt2::asin;
        using nt2::atan;
        using nt2::atan2;
        using nt2::cosh;
        using nt2::sinh;
        using nt2::tanh;
        using nt2::atanh;
        using nt2::asinh;
        using nt2::acosh;
        using nt2::erf;
        using nt2::erfc;
        using nt2::log1p;
        using nt2::expm1;
        using nt2::gamma;
        using nt2::boost_math::lgamma;
        using nt2::boost_math::tgamma;
        using nt2::trunc;
        using nt2::copysign;
        using nt2::hypot;
        using nt2::log;
        ALIAS(nt2::is_inf, isinf)
        using nt2::pow;
        long pow(long n, long m) { return pow(n,m); }

        double const pi = std::atan(1)*4;
        double const e = std::exp(1);

        std::tuple<double,long> frexp(double x)
        {
            int exp;
            double sig = std::frexp(x,&exp);
            return std::tuple<double,long>(sig,exp);
        }


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
        PROXY(pythonic::math,log2);
        PROXY(pythonic::math,isnan);
        PROXY(pythonic::math,ceil);
        PROXY(pythonic::math,floor);
        PROXY(pythonic::math,pow);
    }
}

#endif
