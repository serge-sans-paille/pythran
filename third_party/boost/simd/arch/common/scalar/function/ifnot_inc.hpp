//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IFNOT_INC_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IFNOT_INC_HPP_INCLUDED

#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
 BOOST_DISPATCH_OVERLOAD ( ifnot_inc_
                         , (typename A0, typename A1)
                         , bd::cpu_
                         , bd::scalar_< bd::fundamental_<A0> >
                         , bd::scalar_< bd::arithmetic_<A1> >
                         )
  {
    BOOST_FORCEINLINE A1 operator() ( A0 a0, A1 a1) const BOOST_NOEXCEPT
    {
      return a0 ? a1 :a1+A1(1);
    }
  };
} } }


#endif
