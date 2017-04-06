//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_MULTIPLIES_S_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_MULTIPLIES_S_HPP_INCLUDED

#include <boost/simd/constant/valmax.hpp>
#include <boost/simd/constant/valmin.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/bitofsign.hpp>
#include <boost/simd/function/bitwise_xor.hpp>
#include <boost/simd/function/genmask.hpp>
#include <boost/simd/function/saturate.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_unsigned.hpp>
#include <boost/simd/detail/dispatch/meta/upgrade.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( multiplies_
                          , (typename A0)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const saturated_tag &,  A0 a0, A0 a1
                                    ) const BOOST_NOEXCEPT
    {
      return a0*a1;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( multiplies_
                          , (typename A0)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bd::scalar_< bd::unsigned_<A0> >
                          , bd::scalar_< bd::unsigned_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const saturated_tag &,  A0 a0, A0 a1
                                    ) const BOOST_NOEXCEPT
    {
      using up_t =  bd::upgrade_t<A0>;
      up_t res = up_t(a0)*up_t(a1);
      return static_cast<A0>(res) | genmask(static_cast<A0>(res >> sizeof(A0)*CHAR_BIT));
    }
  };
  BOOST_DISPATCH_OVERLOAD ( multiplies_
                          , (typename A0)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bd::scalar_< bd::integer_<A0> >
                          , bd::scalar_< bd::integer_<A0> >
                          )
  {

    BOOST_FORCEINLINE A0 operator() (const saturated_tag &,  A0 a0, A0 a1
                                    ) const BOOST_NOEXCEPT
    {
      using up_t =  bd::upgrade_t<A0>;
      return A0(saturate<A0>(static_cast<up_t>(a0)*static_cast<up_t>(a1)));
    }
  };
  BOOST_DISPATCH_OVERLOAD ( multiplies_
                          , (typename A0)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bd::scalar_< bd::int32_<A0> >
                          , bd::scalar_< bd::int32_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const saturated_tag &,  A0 a0, A0 a1
                                    ) const BOOST_NOEXCEPT
    {
      using un_t = bd::as_unsigned_t<A0>;
      using up_t = bd::upgrade_t<A0>;

      up_t res = up_t(a0)*up_t(a1);
      un_t res2 = (un_t(a0 ^ a1) >> (sizeof(A0)*CHAR_BIT-1)) + Valmax<A0>();

      A0 hi = (res >> sizeof( A0)*CHAR_BIT);
      A0 lo = res;

      if(hi != (lo >> (sizeof( A0)*CHAR_BIT-1)))
        res = res2;

      return res;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( multiplies_
                          , (typename A0)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bd::scalar_< bd::uint64_<A0> >
                          , bd::scalar_< bd::uint64_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const saturated_tag &,  A0 a0, A0 a1
                                    ) const BOOST_NOEXCEPT
    {
      if (a1 == 0 || a0 == 0) return Zero<A0>();
      if (a1 >= a0)
        return aux(a0, a1);
      else
        return aux(a1, a0);
    }
  private :
    static BOOST_FORCEINLINE A0 aux(const A0& mini,  const A0& maxi)
    {
      A0 z = Valmax<A0>()/maxi;
      return (z < mini) ? Valmax<A0>() : mini*maxi;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( multiplies_
                          , (typename A0)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bd::scalar_< bd::int64_<A0> >
                          , bd::scalar_< bd::int64_<A0> >
                          )
  {
    using un_t = bd::as_unsigned_t<A0>;
    BOOST_FORCEINLINE A0 operator() (const saturated_tag &,  A0 a0, A0 a1
                                    ) const BOOST_NOEXCEPT
    {
      if (a1 == 0 || a0 == 0) return Zero<A0>();
      A0 sgn =  bitwise_xor(bitofsign(a0), bitofsign(a1));
      un_t aa0 = simd::abs(a0);
      un_t aa1 = simd::abs(a1);
      if (aa1 >= aa0)
        return aux(a0, a1, sgn, aa0, aa1);
      else
        return aux(a1, a0, sgn, aa1, aa0);
    }
    static BOOST_FORCEINLINE A0 aux(const A0& mini,  const A0& maxi,
                                    const A0& sgn,
                                    const un_t& amini, const un_t& amaxi)
    {
      un_t z = Valmax<A0>()/amaxi;
      return (z < amini)
        ? ( sgn ? Valmin<A0>():Valmax<A0>())
        : mini*maxi;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( multiplies_
                          , (typename A0)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bd::scalar_< bd::fundamental_<A0> >
                          , bd::scalar_< bd::fundamental_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const saturated_tag &,  A0 a0, A0 a1
                                    ) const BOOST_NOEXCEPT
    {
      return saturated_(multiplies(a0, a1));
    }
  };

} } }


#endif
