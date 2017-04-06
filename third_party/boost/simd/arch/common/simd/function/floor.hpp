//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_FLOOR_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_FLOOR_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/trunc.hpp>
#include <boost/simd/function/if_dec.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( floor_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::floating_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
    {
      const A0 d0 = trunc(a0);
      return if_dec(d0>a0,d0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( floor_
                          , (typename A0)
                          , bd::cpu_
                          , bd::generic_< bd::integer_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator()(A0 const& a0) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };
} } }

#endif
