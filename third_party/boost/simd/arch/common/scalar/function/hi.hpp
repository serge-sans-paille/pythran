//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_HI_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_HI_HPP_INCLUDED

#include <boost/simd/function/lo.hpp>
#include <boost/simd/function/shr.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>
#include <boost/config.hpp>
namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( hi_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    using result_t = bd::as_integer_t<A0,unsigned>;

    BOOST_FORCEINLINE result_t operator() ( A0 const& a0) const BOOST_NOEXCEPT
    {
      return lo( shr(a0, sizeof(result_t)*(CHAR_BIT/2)));
    }
  };


} } }


#endif
