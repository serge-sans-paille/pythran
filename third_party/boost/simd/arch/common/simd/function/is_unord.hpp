//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IS_UNORD_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IS_UNORD_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/constant/false.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/meta/as_logical.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

   BOOST_DISPATCH_OVERLOAD_IF(is_unord_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::integer_<A0>, X>
                          , bs::pack_<bd::integer_<A0>, X>
                          )
   {
     using result = bs::as_logical_t<A0>;
     BOOST_FORCEINLINE result operator()( const A0&,  const A0& ) const BOOST_NOEXCEPT
     {
       return False<result>();
     }
   };
   BOOST_DISPATCH_OVERLOAD_IF(is_unord_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
     using result = bs::as_logical_t<A0>;
     BOOST_FORCEINLINE result operator()( const A0& a0,  const A0& a1) const BOOST_NOEXCEPT
     {
       return a0!=a0 || a1!=a1;
     }
   };

} } }


#endif

