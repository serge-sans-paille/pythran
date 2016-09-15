//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IDIVFIX_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IDIVFIX_HPP_INCLUDED

#include <boost/simd/function/fix.hpp>
#include <boost/simd/function/ifix.hpp>
#include <boost/simd/function/divides.hpp>
#include <boost/simd/function/toint.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD_IF ( div_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::tag::ifix_
                          , bs::pack_< bd::arithmetic_<A0>, X>
                          , bs::pack_< bd::arithmetic_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( bd::functor<bs::tag::ifix_> const&
                                    ,  A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
    {
      return div(fix, a0, a1);
    }
  };

#ifdef BOOST_MSVC
  #pragma warning(push)
  #pragma warning(disable: 4723) // potential divide by 0
#endif

  BOOST_DISPATCH_OVERLOAD_IF ( div_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::tag::ifix_
                          , bs::pack_< bd::floating_<A0>, X>
                          , bs::pack_< bd::floating_<A0>, X>
                          )

  {
    BOOST_FORCEINLINE bd::as_integer_t<A0> operator() ( bd::functor<bs::tag::ifix_> const&
                                    ,  A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
    {
      return saturated_(toint)(a0/a1);
    }
  };
} } }

#ifdef BOOST_MSVC
  #pragma warning(pop)
#endif

#endif
