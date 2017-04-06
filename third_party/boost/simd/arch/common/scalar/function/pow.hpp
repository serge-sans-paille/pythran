//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_POW_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_POW_HPP_INCLUDED
#include <boost/simd/function/std.hpp>

#include <boost/simd/arch/common/detail/generic/pow_expander.hpp>
#include <boost/simd/constant/mone.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/nan.hpp>
#include <boost/simd/function/is_flint.hpp>
#include <boost/simd/function/is_inf.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/function/is_negative.hpp>
#include <boost/simd/function/is_odd.hpp>
#include <boost/simd/function/pow_abs.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( pow_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    inline A0 operator() ( A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      auto ltza0 = is_ltz(a0);
      auto isinfa1 = is_inf(a1);
      if( a0 == Mone<A0>() && isinfa1 ) return One<A0>();
      if( ltza0 && !is_flint(a1) && !is_inf(a1) ) return Nan<A0>();
      A0 z = pow_abs(a0, a1);
      if (isinfa1) return z;
      return  (is_negative(a0) && is_odd(a1)) ? -z : z;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( pow_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    inline A0 operator() (const std_tag &,  A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      return std::pow(a0, a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( pow_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          , bd::constant_< bd::uint_<A1> >
                          )
  {
    using result_type = A0;

    BOOST_FORCEINLINE result_type operator() ( A0 a0, A1) const BOOST_NOEXCEPT
    {
      return pow_expander<A1::value>::call(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( pow_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::constant_< bd::int_<A1> >
                          )
  {
    using result_type = A0;

    BOOST_FORCEINLINE result_type operator() ( A0  a0, A1) const BOOST_NOEXCEPT
    {
      return eval(a0, boost::mpl::bool_<(A1::value >= 0)>());
    }

    BOOST_FORCEINLINE result_type eval( A0  a0, boost::mpl::true_) const BOOST_NOEXCEPT
    {
      return pow_expander<A1::value>::call(a0);
    }

    BOOST_FORCEINLINE result_type eval( A0  a0, boost::mpl::false_) const BOOST_NOEXCEPT
    {
      return pow_expander<-A1::value>::call(rec(a0));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( pow_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          , bd::scalar_< bd::uint_<A1> >
                          )
  {
    using result_type = A0;

    A0 operator() ( A0  a0, A1  a1) const BOOST_NOEXCEPT
    {
      A0 base = a0;
      A1 expo = a1;

      result_type result = One<result_type>();
      while(expo)
      {
        if(is_odd(expo))
          result *= base;
        expo >>= 1;
        base = sqr(base);
      }

      return result;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( pow_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< bd::integer_<A0> >
                          , bd::scalar_< bd::int_<A1> >
                          )
  {
    using result_type = A0;

    BOOST_FORCEINLINE A0 operator() ( A0  a0, A1  a1) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG( boost::simd::assert_all(a1 >= 0), "integral pow with signed exponent" );

      using u_t =  bd::as_integer_t<A1, unsigned>;
      return pow(a0, bitwise_cast<u_t>(a1));
    }
  };


  BOOST_DISPATCH_OVERLOAD ( pow_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::int_<A1> >
                          )
  {
    using result_type = A0;

    A0 operator() ( A0  a0, A1  a1) const BOOST_NOEXCEPT
    {
      using u_t =  bd::as_integer_t<A1, unsigned>;
      auto ltza1 = is_ltz(a1);
      A0 p = pow(a0, bitwise_cast<u_t>(ltza1? -a1 : a1));
      return ltza1 ? rec(p) : p;
    }
  };
} } }


#endif
