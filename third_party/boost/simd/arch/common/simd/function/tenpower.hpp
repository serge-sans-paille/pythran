//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_TENPOWER_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_TENPOWER_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/ten.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/any.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/function/is_odd.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/rec.hpp>
#include <boost/simd/function/shift_right.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/detail/dispatch/meta/as_floating.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF(tenpower_
                             , (typename A0, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::pack_<bd::int_<A0>, X>
                             )
   {
      using result = bd::as_floating_t<A0>;
      BOOST_FORCEINLINE result operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        result res = One<result>();
        result base = Ten<result>();
        A0 expo = bs::abs(a0);
        while(any(expo))
        {
          //       res *= if_else(is_odd(expo), base, One<result>()); TO DO
          res =  res * if_else(is_odd(expo), base, One<result>());
          //  expo >>= 1; TODO
          expo =  shift_right(expo, 1);
          base = sqr(base);
        }
        return if_else(is_ltz(a0), bs::rec(res), res);
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF(tenpower_
                             , (typename A0, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::pack_<bd::uint_<A0>, X>
                             )
   {
      using result = bd::as_floating_t<A0>;
      BOOST_FORCEINLINE result operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        result res = One<result>();
        result base = Ten<result>();
        A0 expo = a0;
        while(any(expo))
        {
          res = res*if_else(is_odd(expo), base, One<result>()); // TODO
//          res *= if_else(is_odd(expo), base, One<result>());
          //  expo >>= 1; TODO
          expo =  shift_right(expo, 1);
          base = sqr(base);
        }
        return res;
      }
   };

} } }


#endif

