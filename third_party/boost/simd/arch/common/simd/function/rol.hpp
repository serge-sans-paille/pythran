//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ROL_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ROL_HPP_INCLUDED

#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/meta/cardinal_of.hpp>
#include <boost/simd/detail/assert_utils.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/bitwise_or.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/function/shift_left.hpp>
#include <boost/simd/function/shift_right.hpp>
#include <boost/simd/function/splat.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( rol_
                          , (typename A0, typename A1, typename X)
                          , bd::cpu_
                          , bs::pack_< bd::unsigned_<A0>, X>
                          , bd::scalar_< bd::unsigned_<A1> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 const& a0, A1 a1) const
    {
      BOOST_ASSERT_MSG(assert_good_shift<A0>(a1), "rol : rotation is out of range");

      using s_t = bd::scalar_of_t<A0>;
      static const A1 width = sizeof(s_t)*CHAR_BIT-1;
      A1 n(a1);
      return (shift_left(a0, n)) | (shift_right(a0, (-n&width)));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( rol_
                          , (typename A0, typename A1, typename X)
                          , bd::cpu_
                          , bs::pack_< bd::arithmetic_<A0>, X>
                          , bd::scalar_< bd::integer_<A1> >
  )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 const&  a0, A1 a1 ) const
    {
      using i_t  = bd::as_integer_t<A0, unsigned>;
      using is_t = bd::as_integer_t<i_t, unsigned>;
      return bitwise_cast<A0>( rol ( bitwise_cast<i_t>(a0)
                                   , is_t(a1)
                                   )
                             );
    }
  };


  BOOST_DISPATCH_OVERLOAD_IF ( rol_
                             , (typename A0, typename A1, typename X)
                             , ( nsm::and_<
                                 detail::is_native<X>,
                                 nsm::bool_<bs::cardinal_of<A0>::value == bs::cardinal_of<A1>::value>
                                 >
                               )
                             , bd::cpu_
                             , bs::pack_< bd::unsigned_<A0>, X>
                             , bs::pack_< bd::unsigned_<A1>, X>
                             )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 const& a0, A1 const& a1 ) const
    {
      using s_t = bd::scalar_of_t<A0>;
      BOOST_ASSERT_MSG(assert_good_shift<A0>(a1), "rol : rotation is out of range");

      s_t static const width = sizeof(s_t)*CHAR_BIT;
      return shift_left(a0, a1) | shift_right(a0, (width-a1) & (width-1));
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( rol_
                          , (typename A0, typename A1, typename X)
                          , ( nsm::and_<
                              detail::is_native<X>,
                              nsm::bool_<bs::cardinal_of<A0>::value == bs::cardinal_of<A1>::value>
                              >
                             )
                          , bd::cpu_
                          , bs::pack_< bd::arithmetic_<A0>, X>
                          , bs::pack_< bd::integer_<A1>, X>
  )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 const& a0, A1 const& a1 ) const
    {
      using i_t = bd::as_integer_t<A0, unsigned>;
      return bitwise_cast<A0>( rol ( bitwise_cast<i_t>(a0)
                                   , bitwise_cast<i_t>(a1)
                                   )
                             );
    }
  };
} } }


#endif
