//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ASECPI_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ASECPI_HPP_INCLUDED

#include <boost/simd/function/asec.hpp>
#include <boost/simd/constant/invpi.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD_IF ( asecpi_
                          , (typename A0, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                            , bs::pack_< bd::floating_<A0>, X>
                            )
  {
    using result_t = A0;
    A0 operator() ( A0 const& a0) const
    {
      return bs::Invpi<A0>()*bs::asec(a0);
    }
  };
} } }


#endif
