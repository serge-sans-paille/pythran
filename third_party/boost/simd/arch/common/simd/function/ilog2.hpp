//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ILOG2_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ILOG2_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/clz.hpp>
#include <boost/simd/function/exponent.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/function/splat.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/detail/assert_utils.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF(ilog2_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
      using result = bd::as_integer_t<A0>;
      BOOST_FORCEINLINE result operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        BOOST_ASSERT_MSG( assert_all(a0 > 0)
                        , "Logarithm is not defined for zero or negative values." );
        return bs::exponent(a0);
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF(ilog2_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::arithmetic_<A0>, X>
                          )
   {
      using result = bd::as_integer_t<A0>;
      BOOST_FORCEINLINE result operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        BOOST_ASSERT_MSG( assert_all(a0 > 0)
                        , "Logarithm is not defined for zero or negative values." );
        return saturated_(dec)(sizeof(bd::scalar_of_t<A0>)*8-bs::clz(bitwise_cast<result>(a0)));
      }
   };

} } }


#endif

