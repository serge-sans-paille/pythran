//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IF_ALLBITS_ELSE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IF_ALLBITS_ELSE_HPP_INCLUDED

#include <boost/simd/constant/allbits.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/logical.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD ( if_allbits_else_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< logical_<A0> >
                          , bd::scalar_< bd::fundamental_<A1> >
                          )
  {
    BOOST_FORCEINLINE A1 operator() ( A0 a0, A1 a1) const BOOST_NOEXCEPT
    {
      return  a0 ? Allbits<A1>() : a1;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( if_allbits_else_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< bd::fundamental_<A0> >
                          , bd::scalar_< bd::fundamental_<A1> >
                          )
  {
    using result_t = A1;
    BOOST_FORCEINLINE result_t operator() ( A0 a0, A1 a1) const BOOST_NOEXCEPT
    {
      return  is_nez(a0) ? Allbits<A1>() : a1;
    }
  };
} } }


#endif
