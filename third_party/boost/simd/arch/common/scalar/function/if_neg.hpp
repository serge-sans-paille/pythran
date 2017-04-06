//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IF_NEG_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IF_NEG_HPP_INCLUDED

#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( if_neg_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< bd::unspecified_<A0> >
                          , bd::scalar_< bd::signed_<A1> >
                          )
  {
    BOOST_FORCEINLINE A1 operator() ( A0 const& a0, A1 a1) const BOOST_NOEXCEPT
    {
      return is_nez(a0) ? -a1 : a1;
    }
  };
} } }


#endif
