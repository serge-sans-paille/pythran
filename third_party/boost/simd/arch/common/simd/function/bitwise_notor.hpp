//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_BITWISE_NOTOR_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_BITWISE_NOTOR_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/function/bitwise_or.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/complement.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF(bitwise_notor_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::arithmetic_<A0>, X>
                          , bs::pack_<bd::arithmetic_<A0>, X>
                          )
   {
     BOOST_FORCEINLINE A0 operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
     {
       return bitwise_or(complement(a0), a1);
     }
   };

  BOOST_DISPATCH_OVERLOAD_IF(bitwise_notor_
                         , (typename A0, typename A1, typename X)
                         , (detail::is_native<X>)
                         , bd::cpu_
                         , bs::pack_<bd::arithmetic_<A0>, X>
                         , bs::pack_<bd::arithmetic_<A1>, X>
                         )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0, const  A1&  a1) const BOOST_NOEXCEPT
    {
      return bitwise_notor(a0, bitwise_cast<A0>(a1));
    }
  };
} } }

#endif

