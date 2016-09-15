//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_MAKE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_MAKE_HPP_INCLUDED

#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD ( make_
                          , (typename Target, typename A0)
                          , bd::cpu_
                          , bd::target_< bd::scalar_<bd::unspecified_<Target>> >
                          , bd::scalar_< bd::unspecified_<A0> >
                          )
  {
    using target_t = typename Target::type;
    BOOST_FORCEINLINE target_t operator()(Target const&, A0 const& a0) const BOOST_NOEXCEPT
    {
      return static_cast<target_t>(a0);
    }
  };
} } }

#endif
