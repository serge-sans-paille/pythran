//==================================================================================================
/*!
  @file

  @copyright 2015 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SINCOSD_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SINCOSD_HPP_INCLUDED

#include <boost/simd/arch/common/detail/scalar/trigo.hpp>
#include <boost/simd/function/restricted.hpp>
#include <boost/simd/arch/common/detail/tags.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( sincosd_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    using result_t = std::pair<A0, A0>                     ;
    BOOST_FORCEINLINE result_t operator() ( A0 a0) const
    {
      return detail::trig_base <A0,tag::degree_tag,tag::not_simd_type,tag::big_tag>::sincosa(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( sincosd_
                          , (typename A0)
                          , bd::cpu_
                          , bs::restricted_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE std::pair<A0, A0> operator() (const restricted_tag &,  A0 a0) const BOOST_NOEXCEPT
    {
      return detail::trig_base<A0, tag::degree_tag,tag::not_simd_type,tag::clipped_pio4_tag>::sincosa(a0);
    }
  };
} } }

#endif
