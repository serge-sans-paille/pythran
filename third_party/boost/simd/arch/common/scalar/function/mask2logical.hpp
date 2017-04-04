//==================================================================================================
/*!
  @file

  @copyright 2015 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_MASK2LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_MASK2LOGICAL_HPP_INCLUDED

#include <boost/simd/constant/allbits.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/assert.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( mask2logical_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    auto operator() ( A0 a0) const BOOST_NOEXCEPT -> decltype(is_nez(a0))
    {
      BOOST_ASSERT_MSG((a0 != A0(0)) || (a0 != Allbits<A0>()), "Argument to mask2logical is not a valid logical mask");
      return is_nez(a0);
    }
  };
} } }


#endif
