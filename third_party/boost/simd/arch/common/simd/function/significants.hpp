//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SIGNIFICANTS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SIGNIFICANTS_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/meta/cardinal_of.hpp>
#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/detail/assert_utils.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/divides.hpp>
#include <boost/simd/function/iceil.hpp>
#include <boost/simd/function/if_zero_else.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/is_gtz.hpp>
#include <boost/simd/function/log10.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/round.hpp>
#include <boost/simd/function/tenpower.hpp>
#include <boost/assert.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>

#ifndef BOOST_SIMD_NO_INVALIDS
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_invalid.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

   BOOST_DISPATCH_OVERLOAD_IF( significants_
                             , (typename A0, typename A1, typename X)
                             , ( nsm::and_<
                                 detail::is_native<X>,
                                 nsm::bool_<bs::cardinal_of<A0>::value == bs::cardinal_of<A1>::value>
                                 >
                               )
                             , bd::cpu_
                             , bs::pack_< bd::floating_<A0>, X>
                             , bs::pack_< bd::integer_<A1>, X>
                             )
   {
     BOOST_FORCEINLINE A0 operator()( const A0& a0, const  A1&  a1) const BOOST_NOEXCEPT
     {
       BOOST_ASSERT_MSG( assert_all(is_gtz(a1))
                       , "Number of significant digits must be positive"
                       );
       using iA0 =  bd::as_integer_t<A0>;
       iA0 expo = bitwise_cast<iA0>(a1) - iceil(log10(abs(a0)));
       A0 fac       = tenpower(expo);
       A0 scaled    = round(a0*fac);
#ifndef BOOST_SIMD_NO_INVALIDS
       A0 r = if_else(is_invalid(a0), a0, scaled/fac);
#else
       A0 r =  scaled/fac;
#endif
       return if_zero_else(is_eqz(a0), r);
     }
   };

  BOOST_DISPATCH_OVERLOAD( significants_
                         , (typename A0, typename A1, typename X)
                         , bd::cpu_
                         , bs::pack_< bd::floating_<A0>, X>
                         , bd::scalar_< bd::integer_<A1>>
                         )
  {

    BOOST_FORCEINLINE A0 operator()( const A0& a0, A1 a1 ) const BOOST_NOEXCEPT
    {
      using iA0 = bd::as_integer_t<A0>;
      return significants(a0, iA0(a1));
    }
  };

} } }


#endif
