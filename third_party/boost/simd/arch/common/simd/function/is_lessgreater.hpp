//==================================================================================================
/*!
  @file
  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IS_LESSGREATER_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IS_LESSGREATER_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/function/logical_and.hpp>
#include <boost/simd/function/is_ord.hpp>
#include <boost/simd/function/is_not_equal.hpp>
#include <boost/simd/logical.hpp>
#include <boost/simd/meta/as_logical.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF ( is_lessgreater_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_< bd::fundamental_<A0>, X >
                          , bs::pack_< bd::fundamental_<A0>, X >
                          )
  {
    BOOST_FORCEINLINE
    bs::as_logical_t<A0> operator()(A0 const& a0 , A0 const& a1) const BOOST_NOEXCEPT
    {
      return  a0 != a1;
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( is_lessgreater_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_< bd::floating_<A0>, X >
                          , bs::pack_< bd::floating_<A0>, X >
                          )
  {
    BOOST_FORCEINLINE
    bs::as_logical_t<A0> operator()(A0 const& a0 , A0 const& a1) const BOOST_NOEXCEPT
    {
      return logical_and(is_ord(a0,a1), (a0 != a1));
    }
  };

} } }


#endif
