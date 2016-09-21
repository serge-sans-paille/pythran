//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SIGNNZ_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SIGNNZ_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/signmask.hpp>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/bitwise_or.hpp>
#include <boost/simd/function/shift_right.hpp>

#ifndef BOOST_SIMD_NO_NANS
#include <boost/simd/function/if_allbits_else.hpp>
#include <boost/simd/function/is_nan.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF(signnz_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::integer_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        using sA0 = bd::scalar_of_t<A0>;
        return bitwise_or(shift_right(a0, (sizeof(sA0)*8-1)), One<A0>());
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF(signnz_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::unsigned_<A0>, X>
                          )
   {
     BOOST_FORCEINLINE A0 operator()(const A0&) const
      {
        return One<A0>();
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF(signnz_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        #ifndef BOOST_SIMD_NO_NANS
        return if_allbits_else(is_nan(a0), bitwise_or(One<A0>(), bitwise_and(Signmask<A0>(), a0)));
        #else
        return bitwise_or(One<A0>(), bitwise_and(Signmask<A0>(), a0));
        #endif
        ;
      }
   };


} } }

#endif

