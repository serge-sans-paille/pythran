//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_EXPONENTBITS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_EXPONENTBITS_HPP_INCLUDED

#include <boost/simd/detail/constant/maxexponent.hpp>
#include <boost/simd/constant/nbmantissabits.hpp>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( exponentbits_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE bd::as_integer_t<A0> operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return bitwise_and((2*Maxexponent<A0>()+1)<<Nbmantissabits<A0>(), a0);
    }
  };
} } }


#endif
