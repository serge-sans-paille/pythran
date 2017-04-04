//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_FNMA_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_FNMA_HPP_INCLUDED

#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/unary_minus.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD_IF ( fnma_
                             , (typename A0, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::pack_< bd::arithmetic_<A0>, X>
                             , bs::pack_< bd::arithmetic_<A0>, X>
                             , bs::pack_< bd::arithmetic_<A0>, X>
                             )
  {
    BOOST_FORCEINLINE
      A0 operator() ( A0 const& a0, A0 const& a1, A0 const& a2) const BOOST_NOEXCEPT
    {
      return -multiplies(a0, a1)-a2;
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( fnma_
                             , (typename A0, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::pedantic_tag
                             , bs::pack_< bd::arithmetic_<A0>, X>
                             , bs::pack_< bd::arithmetic_<A0>, X>
                             , bs::pack_< bd::arithmetic_<A0>, X>
                             )
  {
    BOOST_FORCEINLINE
      A0 operator() (pedantic_tag const &,  A0 const& a0, A0 const& a1, A0 const& a2) const BOOST_NOEXCEPT
    {
      return -pedantic_(fma)(a0, a1, a2);
    }
  };

} } }


#endif
