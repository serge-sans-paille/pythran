//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_GENERIC_FUNCTION_GENMASK_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_GENERIC_FUNCTION_GENMASK_HPP_INCLUDED

#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/meta/hierarchy/logical.hpp>
#include <boost/simd/meta/as_arithmetic.hpp>
#include <boost/simd/constant/allbits.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  // -----------------------------------------------------------------------------------------------
  // re-targeted genmask for logical
  BOOST_DISPATCH_OVERLOAD ( genmask_
                          , (typename A0, typename Target)
                          , bd::cpu_
                          , bd::scalar_< bs::logical_<A0> >
                          , bd::target_< bd::generic_<bd::unspecified_<Target> > >
                          )
  {
    using result_t = typename Target::type;

    BOOST_FORCEINLINE result_t operator()( A0 const& a0, Target const& ) const BOOST_NOEXCEPT
    {
      return a0 ? Allbits<result_t>() : Zero<result_t>();
    }
  };

  // -----------------------------------------------------------------------------------------------
  // re-targeted genmask for other types
  BOOST_DISPATCH_OVERLOAD ( genmask_
                          , (typename A0, typename Target)
                          , bd::cpu_
                          , bd::scalar_< bd::unspecified_<A0> >
                          , bd::target_< bd::generic_<bd::unspecified_<Target> > >
                          )
  {
    using result_t = typename Target::type;
    BOOST_FORCEINLINE result_t operator()( A0 const& a0, Target const& ) const BOOST_NOEXCEPT
    {
      return (a0!=0) ? Allbits<result_t>() : Zero<result_t>();
    }
  };
} } }

#endif
