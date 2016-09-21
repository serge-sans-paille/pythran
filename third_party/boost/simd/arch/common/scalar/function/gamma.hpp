//==================================================================================================
/*!
  @file
  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_GAMMA_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_GAMMA_HPP_INCLUDED

#include <boost/simd/function/std.hpp>
#include <boost/config.hpp>
#include <boost/simd/arch/common/detail/generic/gamma_kernel.hpp>
#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/constant/nan.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/pi.hpp>
#include <boost/simd/constant/three.hpp>
#include <boost/simd/constant/two.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/copysign.hpp>
#include <boost/simd/function/floor.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/is_even.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/function/sinpi.hpp>
#include <boost/simd/function/stirling.hpp>

#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  using bs::std_tag;
  BOOST_DISPATCH_OVERLOAD ( gamma_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (A0 a0) const BOOST_NOEXCEPT
    {
      if (is_eqz(a0)) return copysign(Inf<A0>(), a0);
      #ifndef BOOST_SIMD_NO_INVALIDS
      if( is_nan(a0) || (a0 == Minf<A0>()) ) return Nan<A0>();
      if (a0 == Inf<A0>()) return a0;
      #endif

      A0 x = a0;
      if (inftest(a0)) return Inf<A0>();
      A0 q = bs::abs(x);
      if(x < A0(-33.0))
      {
//        return std::tgamma(a0);
        A0 st = stirling(q);
        A0 p =  floor(q);
        auto iseven =  is_even((int32_t)p);
        if (p == q) return Nan<A0>();
        A0 z = q - p;
        if( z > Half<A0>() )
        {
          p += One<A0>();
          z = q - p;
        }
        z = q*sinpi(z);
        if( is_eqz(z) ) return Nan<A0>();
        st = Pi<A0>()/(bs::abs(z)*st);
        return iseven  ? -st : st;
      }
      A0 z = One<A0>();
      while( x >= Three<A0>() )
      {
        x -= One<A0>();
        z *= x;
      }
      while( is_ltz(x) )
      {
        z /= x;
        x += One<A0>();
      }
      while( x < Two<A0>() )
      {
        if( is_eqz(x)) return Nan<A0>();
        z /= x;
        x +=  One<A0>();
      }
      if( x == Two<A0>() ) return(z);
      x -= Two<A0>();
      return z*detail::gamma_kernel<A0>::gamma1(x);
    }
  private:
    static BOOST_FORCEINLINE bool inftest(const float a0)
    {
      return a0 > 35.4f;
    }
    static BOOST_FORCEINLINE bool inftest(const double a0)
    {
      return a0 > 171.624;
    }

  };
  BOOST_DISPATCH_OVERLOAD ( gamma_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &, A0 a0) const BOOST_NOEXCEPT
    {
      return std::tgamma(a0);
    }
  };
} } }


#endif
