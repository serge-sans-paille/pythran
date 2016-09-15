//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_FREXP_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_FREXP_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/detail/constant/limitexponent.hpp>
#include <boost/simd/detail/constant/mask1frexp.hpp>
#include <boost/simd/detail/constant/mask2frexp.hpp>
#include <boost/simd/detail/constant/maxexponentm1.hpp>
#include <boost/simd/constant/nbmantissabits.hpp>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/bitwise_andnot.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/bitwise_or.hpp>
#include <boost/simd/function/if_else_zero.hpp>
#include <boost/simd/function/is_greater.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/function/logical_notand.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/if_plus.hpp>
#include <boost/simd/function/shr.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <utility>

#ifndef BOOST_SIMD_NO_DENORMALS
#include <boost/simd/function/is_less.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/logical_and.hpp>
#include <boost/simd/constant/twotonmb.hpp>
#include <boost/simd/constant/smallestposval.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD(frexp_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
     using i_t = bd::as_integer_t<A0, signed>;
     BOOST_FORCEINLINE std::pair<A0,i_t> operator()(A0 const& a0) const
     {
       A0 r0;
       i_t r1;
       using s_type = bd::scalar_of_t<A0>;
#ifndef BOOST_SIMD_NO_DENORMALS
       auto test = logical_and(is_less(bs::abs(a0), Smallestposval<A0>()), is_nez(a0));
       A0 aa0 = if_else(test, Twotonmb<A0>()*a0, a0);
       i_t t = if_else_zero(test,Nbmantissabits<A0>());
#else
       A0 aa0 = a0;
#endif
       r1 = simd::bitwise_cast<i_t>(bitwise_and(aa0, Mask1frexp<A0>())); //extract exp.
       A0 x = bitwise_andnot(aa0, Mask1frexp<A0>());
       r1 = shr(r1,Nbmantissabits<s_type>()) - Maxexponentm1<A0>();
       r0 = bitwise_or(x,Mask2frexp<A0>());
       auto test0 = is_nez(aa0);
       auto test1 = is_greater(r1,Limitexponent<A0>());
       r1 = if_else_zero(logical_notand(test1, test0), r1);
#ifndef BOOST_SIMD_NO_DENORMALS
       r1 -= t ;
#endif
       r0 = if_else_zero(test0, if_plus(test1,r0,aa0));
       return {r0, r1};
     }
   };

  BOOST_DISPATCH_OVERLOAD( frexp_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , boost::simd::fast_tag
                          , bs::pack_< bd::floating_<A0>, X>
                          )
  {
    using i_t = bd::as_integer_t<A0, signed>;
    using sA0 = bd::scalar_of_t<A0>;
    BOOST_FORCEINLINE std::pair<A0,i_t> operator() (const fast_tag &
                                                   , A0 const& a0 ) const BOOST_NOEXCEPT
    {
      i_t r1  = bitwise_cast<i_t>(bitwise_and(Mask1frexp<A0>(), a0));
      A0  x = bitwise_andnot(a0, Mask1frexp<A0>());
      return {bitwise_or(x,Mask2frexp<A0>()), shr(r1,Nbmantissabits<sA0>()) - Maxexponentm1<A0>()};
    }
  };

} } }

#endif

