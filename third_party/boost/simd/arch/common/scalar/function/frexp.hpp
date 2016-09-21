//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_FREXP_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_FREXP_HPP_INCLUDED
#include <boost/simd/function/fast.hpp>
#include <boost/simd/function/std.hpp>

#ifndef BOOST_SIMD_NO_DENORMALS
#include <boost/simd/constant/twotonmb.hpp>
#include <boost/simd/function/is_eqz.hpp>
#endif
#include <boost/simd/detail/constant/limitexponent.hpp>
#include <boost/simd/detail/constant/mask1frexp.hpp>
#include <boost/simd/detail/constant/mask2frexp.hpp>
#include <boost/simd/detail/constant/maxexponentm1.hpp>
#include <boost/simd/constant/nbmantissabits.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/bitwise_andnot.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/bitwise_or.hpp>
#include <boost/simd/function/is_invalid.hpp>
#include <boost/simd/function/shr.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <utility>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( frexp_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    using i_t = bd::as_integer_t<A0, signed>;
    BOOST_FORCEINLINE std::pair<A0,i_t> operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      if (a0 == 0 || is_invalid(a0))
      {
        return {a0, Zero<i_t>()};
      }
      else
      {
        i_t r1 = simd::bitwise_cast<i_t>(bitwise_and(Mask1frexp<A0>(), a0));  // extract exp.
#ifndef BOOST_SIMD_NO_DENORMALS
        i_t t = Zero<i_t>();
        if(is_eqz(r1)) // denormal
        {
          a0 *= Twotonmb<A0>();
          r1 = simd::bitwise_cast<i_t>(bitwise_and(Mask1frexp<A0>(), a0));  // extract exp. again
          t = Nbmantissabits<A0>();
        }
#endif
        A0 x  = bitwise_andnot(a0, Mask1frexp<A0>());                    // clear exp. in a0
        r1 = shr(r1,Nbmantissabits<A0>())- Maxexponentm1<A0>();         // compute exp.
        if (r1 > Limitexponent<A0>())
        {
          return {a0, Zero<i_t>()};
        }
#ifndef BOOST_SIMD_NO_DENORMALS
        r1 -= t;
#endif
        return {bitwise_or(x,Mask2frexp<A0>()), r1};
      }
    }
  };

  BOOST_DISPATCH_OVERLOAD ( frexp_
                          , (typename A0)
                          , bd::cpu_
                          , boost::simd::fast_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    using i_t = bd::as_integer_t<A0, signed>;
    BOOST_FORCEINLINE std::pair<A0,i_t> operator() (const fast_tag &
                                                   , A0 a0 ) const BOOST_NOEXCEPT
    {
      i_t r1  = bitwise_cast<i_t>(bitwise_and(Mask1frexp<A0>(), a0));
      A0  x = bitwise_andnot(a0, Mask1frexp<A0>());
      return {bitwise_or(x,Mask2frexp<A0>()), shr(r1,Nbmantissabits<A0>()) - Maxexponentm1<A0>()};
    }
  };
  BOOST_DISPATCH_OVERLOAD ( frexp_
                          , (typename A0)
                          , bd::cpu_
                          , boost::simd::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    using i_t = bd::as_integer_t<A0, signed>;
    BOOST_FORCEINLINE std::pair<A0,i_t> operator() (const std_tag &,  A0 a0
                                                   ) const BOOST_NOEXCEPT
    {
      int e = Zero<int>();
      A0 r = std::frexp(a0, &e);
      return {r, i_t(e)};
    }
  };
} } }


#endif
