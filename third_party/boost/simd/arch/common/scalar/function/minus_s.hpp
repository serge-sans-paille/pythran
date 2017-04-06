//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_MINUS_S_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_MINUS_S_HPP_INCLUDED

#include <boost/simd/constant/valmax.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/min.hpp>
#include <boost/simd/function/saturate.hpp>
#include <boost/simd/function/saturated.hpp>
#include <boost/simd/detail/dispatch/meta/as_signed.hpp>
#include <boost/simd/detail/dispatch/meta/as_unsigned.hpp>
#include <boost/simd/detail/dispatch/meta/upgrade.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( minus_
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
      return a0-a1;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( minus_
                          , (typename A0)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bd::scalar_< bd::int_<A0> >
                          , bd::scalar_< bd::int_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const saturated_tag &,  A0 a0, A0 a1
                                    ) const BOOST_NOEXCEPT
    {
      using sz_t = typename nsm::bool_<sizeof(A0) == 4 || sizeof(A0) == 8>::type;
      return impl(a0, a1, sz_t());
    }

    static BOOST_FORCEINLINE A0 impl( A0 a0, A0 a1
                                    , const tt::false_type &) BOOST_NOEXCEPT
    {
      using u_t = bd::upgrade_t<A0>;
      using s_t = bd::as_signed_t<u_t>;
      return static_cast<A0>(saturate<A0>(s_t(a0)-s_t(a1)));
    }


    static BOOST_FORCEINLINE A0 impl( A0 a0, A0 a1
                                    , const tt::true_type &) BOOST_NOEXCEPT
    {
      using un_t = bd::as_unsigned_t<A0>;

      un_t ux = a0;
      un_t uy = a1;
      un_t res = ux - uy;

      ux = (ux >> (sizeof(A0)*CHAR_BIT-1)) + Valmax<A0>();

      if(A0((ux ^ uy) & (ux ^ res)) < Zero<A0>()) res = ux;

      return res;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( minus_
                          , (typename A0)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bd::scalar_< bd::uint_<A0> >
                          , bd::scalar_< bd::uint_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const saturated_tag &,  A0 a0, A0 a1
                                    ) const BOOST_NOEXCEPT
    {
      A0 res = a0 - a1;
      res &= -(res <= a0);

      return res;
    }
  };
} } }
#endif

