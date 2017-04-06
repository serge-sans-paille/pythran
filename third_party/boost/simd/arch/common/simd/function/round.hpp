//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ROUND_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ROUND_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/constant/half.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/ceil.hpp>
#include <boost/simd/function/logical_andnot.hpp>
#include <boost/simd/function/copysign.hpp>
#include <boost/simd/function/divides.hpp>
#include <boost/simd/function/inc.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_flint.hpp>
#include <boost/simd/function/is_greater.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/none.hpp>
#include <boost/simd/function/nearbyint.hpp>
#include <boost/simd/function/tenpower.hpp>
#include <boost/simd/function/trunc.hpp>
#include <boost/simd/function/unary_minus.hpp>
#include <boost/simd/function/splat.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD(round_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::integer_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        return a0;
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF(round_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        const A0 v = bs::abs(a0);
        const A0 c = bs::ceil(v);
        return if_else(v > Maxflint<A0>(), a0, copysign(if_dec(c-Half<A0>() > v, c), a0));
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF(round_
                             , (typename A0, typename A1, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::pack_<bd::single_<A0>, X>
                             , bs::pack_<bd::integer_<A1>, X>
                             )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0, const  A1&  a1) const BOOST_NOEXCEPT
      {
        A0 fac = tenpower(a1);
        A0 tmp1 = round(a0*fac)/fac;
        return if_else(is_ltz(a1), round(tmp1), tmp1);
      }
   };

   BOOST_DISPATCH_OVERLOAD(round_
                          , (typename A0, typename A1, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          , bd::scalar_<bd::unsigned_<A1>>
                          )
   {
     BOOST_FORCEINLINE A0 operator()(A0 const & a0,  A1 const & a1) const
      {
        using itype_t = bd::as_integer_t<A0, unsigned>;
        return round(a0, splat<itype_t>(a1));
      }
   };

   BOOST_DISPATCH_OVERLOAD(round_
                          , (typename A0, typename X, typename A1)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          , bd::scalar_<bd::integer_<A1>>
                          )
   {
     BOOST_FORCEINLINE A0 operator()(A0 const & a0,  A1 const & a1) const
      {
        using itype_t = bd::as_integer_t<A0>;
        return round(a0, splat<itype_t>(a1));
      }
   };
} } }

#endif
