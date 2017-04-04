//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_FFS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_FFS_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/firstbitset.hpp>
#include <boost/simd/function/genmask.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/inc.hpp>
#include <boost/simd/function/shift_left.hpp>
#include <boost/simd/function/shr.hpp>
#include <boost/simd/function/unary_minus.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>
#include <boost/simd/constant/ratio.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF(ffs_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::type8_<A0>, X>
                          )
   {
      using result = bd::as_integer_t<A0>;
      BOOST_FORCEINLINE result operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        result v = bitwise_cast<result>(firstbitset(a0));
        return  bitwise_and(genmask(v)
                           ,inc(bitwise_or(
                                  bitwise_or(
                                    (-( genmask(bitwise_and(v,result(0xAA)))))
                                    , shift_left(-(genmask(bitwise_and(v, result(0xCC)))),1))
                                  , shift_left(-(genmask(bitwise_and(v, result(0xF0)))),2))));
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF(ffs_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::type16_<A0>, X>
                          )
   {
      using result = bd::as_integer_t<A0>;
      BOOST_FORCEINLINE result operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        result v = bitwise_cast<result>( firstbitset(a0));
        return  bitwise_and(genmask(v)
                           ,inc(bitwise_or(
                                  bitwise_or(
                                    bitwise_or(
                                      (-( genmask(bitwise_and(v, result(0xAAAA)))))
                                      ,shift_left(-( genmask(bitwise_and(v,result(0xCCCC)))),1))
                                    ,shift_left(-( genmask(bitwise_and(v,result(0xF0F0)))),2))
                                  ,shift_left(-( genmask(bitwise_and(v,result(0xFF00)))),3))));
      }
   };

  BOOST_DISPATCH_OVERLOAD_IF(ffs_
                         , (typename A0, typename X)
                         , (detail::is_native<X>)
                         , bd::cpu_
                         , bs::pack_<bd::type32_<A0>, X>
                         )
  {
    using result = bd::as_integer_t<A0>;
    BOOST_FORCEINLINE result operator()( const A0& a0) const BOOST_NOEXCEPT
    {
      result v =  bitwise_cast<result>(firstbitset(a0));
      return  bitwise_and(genmask(v)
                         ,inc(bitwise_or(
                                bitwise_or(
                                  bitwise_or(
                                    bitwise_or(
                                      (-( genmask(bitwise_and(v,result(0xAAAAAAAA)))))
                                      ,shift_left(-(genmask(bitwise_and(v,result(0xCCCCCCCC)))),1))
                                    , shift_left(-(genmask(bitwise_and(v,result(0xF0F0F0F0)))),2))
                                  , shift_left(-(genmask(bitwise_and(v,result(0xFF00FF00)))), 3))
                                , shift_left(-(genmask(bitwise_and(v,result(0xFFFF0000)))),4))));
    }
  };

} } }

#endif
