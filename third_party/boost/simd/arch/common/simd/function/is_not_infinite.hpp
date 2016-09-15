//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IS_NOT_INFINITE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IS_NOT_INFINITE_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/true.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/is_not_equal.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF(is_not_infinite_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::integer_<A0>, X>
                          )
   {
     using result = bs::as_logical_t<A0>;
     BOOST_FORCEINLINE result operator()(const A0&) const BOOST_NOEXCEPT
     {
       return bs::True<result>();
     }
   };

   BOOST_DISPATCH_OVERLOAD_IF(is_not_infinite_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE bs::as_logical_t<A0> operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        return is_not_equal(bs::abs(a0),bs::Inf<A0>());
      }
   };

} } }
#endif

