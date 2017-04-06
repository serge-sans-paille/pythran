//==================================================================================================
/*!
  @file

  @copyright 2015 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ROL_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ROL_HPP_INCLUDED

#include <boost/simd/meta/cardinal_of.hpp>
#include <boost/simd/detail/assert_utils.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( rol_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< bd::unsigned_<A0> >
                          , bd::scalar_< bd::unsigned_<A1> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A0 a1) const
    {
      BOOST_ASSERT_MSG(assert_good_shift<A0>(a1), "rol : rotation is out of range");

      static const A0 width = sizeof(A0)*CHAR_BIT-1;
      A0 n = A0(a1);
      return (a0 << n) | (a0 >> (-n&width));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( rol_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          , bd::scalar_< bd::integer_<A1> >
  )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A1 a1 ) const
    {
      using i_t = bd::as_integer_t<A0, unsigned>;
      return bitwise_cast<A0>( rol ( bitwise_cast<i_t>(a0), i_t(a1)));
    }
  };

} } }


#endif
