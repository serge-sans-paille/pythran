//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_MANTISSA_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_MANTISSA_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/detail/constant/mantissamask.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/bitwise_or.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_eqz.hpp>

#ifndef BOOST_SIMD_NO_INVALIDS
#include <boost/simd/function/is_invalid.hpp>
#include <boost/simd/function/logical_or.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD(mantissa_
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

   BOOST_DISPATCH_OVERLOAD_IF(mantissa_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        A0 r = bitwise_or(bitwise_and(a0,Mantissamask<A0>()),One<A0>());
        #ifndef BOOST_SIMD_NO_INVALIDS
        return if_else(logical_or(is_invalid(a0),is_eqz(a0)),a0,r);
        #else
        return if_else(is_eqz(a0),a0,r);
        #endif
      }
   };


} } }

#endif

