//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ROUND_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ROUND_HPP_INCLUDED

#include <boost/simd/constant/half.hpp>
#include <boost/simd/detail/constant/maxflint.hpp>
#include <boost/simd/function/std.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/ceil.hpp>
#include <boost/simd/function/copysign.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/function/if_dec.hpp>
#include <boost/simd/function/tenpower.hpp>
#include <boost/simd/detail/overload.hpp>
#include <boost/config.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( round_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::integer_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( round_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::single_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      const A0 v = bs::abs(a0);
      if (!(v <=  Maxflint<A0>())) return a0;
      A0 c =  bs::ceil(v);
      return bs::copysign(if_dec(c-Half<A0>() > v, c), a0);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( round_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::double_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      const A0 v = simd::abs(a0);
      if (!(v <=  Maxflint<A0>())) return a0;
      A0 c =  boost::simd::ceil(v);
      return copysign(if_dec(c-Half<A0>() > v, c), a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( round_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                         )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &
                                    ,  A0  a0) const BOOST_NOEXCEPT
    {
      return std::round(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( round_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::integer_<A0> >
                         )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &
                                    ,  A0  a0) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( round_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::int_<A1> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A1 a1) const BOOST_NOEXCEPT
    {
       using i_t = bd::as_integer_t<A0>;
       A0 fac = tenpower(i_t(a1));
       A0 x = a0*fac;
       A0 z = bs::round(x)/fac;
       return is_ltz(a1) ? std::round(z) : z;
    }
  };

   BOOST_DISPATCH_OVERLOAD ( round_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::uint_<A1> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A1 a1) const BOOST_NOEXCEPT
    {
       using i_t = bd::as_integer_t<A0>;
       A0 fac = tenpower(i_t(a1));
       A0 x = a0*fac;
       return  bs::round(x)/fac;
    }
  };
} } }

#endif
