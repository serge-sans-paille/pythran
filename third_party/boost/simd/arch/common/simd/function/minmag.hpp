//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_MINMAG_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_MINMAG_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_not_greater_equal.hpp>
#include <boost/simd/function/min.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF(minmag_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::arithmetic_<A0>, X>
                          , bs::pack_<bd::arithmetic_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        A0 aa0 = abs(a0);
        A0 aa1 = abs(a1);
        return if_else( is_not_greater_equal(aa0, aa1), a0
                      , if_else( is_not_greater_equal(aa1, aa0), a1
                               , bs::min(a0, a1) ) );
      }
   };


} } }

#endif

