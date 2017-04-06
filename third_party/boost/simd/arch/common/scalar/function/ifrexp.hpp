//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IFREXP_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IFREXP_HPP_INCLUDED

#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/function/pedantic.hpp>
#include <boost/simd/function/std.hpp>


#ifndef BOOST_SIMD_NO_DENORMALS
#include <boost/simd/constant/twotonmb.hpp>
#include <boost/simd/function/is_eqz.hpp>
#endif

#include <boost/simd/function/raw.hpp>
#include <boost/simd/function/pedantic.hpp>
#include <boost/simd/function/std.hpp>

#include <boost/simd/detail/constant/limitexponent.hpp>
#include <boost/simd/detail/constant/mask1frexp.hpp>
#include <boost/simd/detail/constant/mask2frexp.hpp>
#include <boost/simd/detail/constant/maxexponentm1.hpp>
#include <boost/simd/constant/nbmantissabits.hpp>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/bitwise_andnot.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/bitwise_or.hpp>
#include <boost/simd/function/is_invalid.hpp>
#include <boost/simd/function/shr.hpp>
#include <boost/config.hpp>
#include <utility>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD ( ifrexp_
                          , (typename A0)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    using i_t = bd::as_integer_t<A0, signed>;
    BOOST_FORCEINLINE std::pair<A0,i_t> operator()(const pedantic_tag &, A0 a0) const BOOST_NOEXCEPT
    {
      if (a0 == 0 || is_invalid(a0))
      {
        return {a0, i_t(0)};
      }
      else
      {
        auto m1f  = Mask1frexp<A0>();
        auto nmb  = Nbmantissabits<A0>();

        i_t r1    = simd::bitwise_cast<i_t>(bitwise_and(m1f, a0));  // extract exp.

#ifndef BOOST_SIMD_NO_DENORMALS
        i_t t = i_t(0);
        if(is_eqz(r1)) // denormal
        {
          a0 *= Twotonmb<A0>();
          r1  = simd::bitwise_cast<i_t>(bitwise_and(m1f, a0));  // extract exp. again
          t   = nmb;
        }
#endif

        A0 x  = bitwise_andnot(a0, m1f);               // clear exp. in a0
        r1 = shr(r1,nmb)- Maxexponentm1<A0>();         // compute exp.
        if (r1 > Limitexponent<A0>()) return {a0, i_t(0)};

#ifndef BOOST_SIMD_NO_DENORMALS
        r1 -= t;
#endif

        return {bitwise_or(x,Mask2frexp<A0>()), r1};
      }
    }
  };

  BOOST_DISPATCH_OVERLOAD ( ifrexp_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    using i_t = bd::as_integer_t<A0, signed>;
    BOOST_FORCEINLINE std::pair<A0,i_t> operator()(A0 a0) const BOOST_NOEXCEPT
    {
      if(!a0) return {A0(0),i_t(0)};
      else    return raw_(simd::ifrexp)(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( ifrexp_
                          , (typename A0)
                          , bd::cpu_
                          , boost::simd::raw_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    using i_t = bd::as_integer_t<A0, signed>;
    BOOST_FORCEINLINE std::pair<A0,i_t> operator()(const raw_tag &,  A0 a0) const BOOST_NOEXCEPT
    {
      auto m1f  = Mask1frexp<A0>();
      auto r1   = bitwise_cast<i_t>(bitwise_and(m1f, a0));
      A0    x   = bitwise_andnot(a0, m1f);

      return  { bitwise_or(x,Mask2frexp<A0>())
              , shr(r1,Nbmantissabits<A0>()) - Maxexponentm1<A0>()
              };
    }
  };

  BOOST_DISPATCH_OVERLOAD ( ifrexp_
                          , (typename A0)
                          , bd::cpu_
                          , boost::simd::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    using i_t = bd::as_integer_t<A0, signed>;
    BOOST_FORCEINLINE std::pair<A0,i_t> operator()(const std_tag &, A0 a0) const BOOST_NOEXCEPT
    {
      int e(0);
      A0 r = std::frexp(a0, &e);
      return {r, i_t(e)};
    }
  };
} } }

#endif
