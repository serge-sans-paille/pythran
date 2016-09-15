//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_GENMASKC_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_GENMASKC_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/constant/allbits.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/complement.hpp>
#include <boost/simd/function/genmask.hpp>
#include <boost/simd/function/if_zero_else.hpp>
#include <boost/simd/function/is_eqz.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF(genmaskc_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::fundamental_<A0>, X>
                          )
   {
     BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT // TODO bool
      {
        return if_zero_else(a0, Allbits<A0>());
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF(genmaskc_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::arithmetic_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        return genmask(is_eqz(a0));
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF(genmaskc_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bs::logical_<A0>, X>
                          )
   {
     template < typename A0_>
     typename enable_if< bs::is_bitwise_logical<A0_>, A0>::type
     BOOST_FORCEINLINE operator()(A0_ const& a0) const BOOST_NOEXCEPT
     {
       return complement(bitwise_cast<typename A0::type>(a0));
     }
   };

} } }

#endif

