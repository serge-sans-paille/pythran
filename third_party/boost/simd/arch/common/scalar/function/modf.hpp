//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_MODF_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_MODF_HPP_INCLUDED
#include <boost/simd/function/std.hpp>

#include <boost/simd/function/trunc.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <boost/fusion/include/std_pair.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( modf_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_ < bd::arithmetic_<A0> >
                          , bd::scalar_ < bd::arithmetic_<A0> >
                          , bd::scalar_ < bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE void operator() ( A0 a0, A0 & frac,A0 & ent) const BOOST_NOEXCEPT
    {
      ent = simd::trunc(a0);
      frac = a0 - ent;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( modf_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_ < bd::arithmetic_<A0> >
                          , bd::scalar_ < bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0,A0 & ent) const BOOST_NOEXCEPT
    {
      A0 frac;
      simd::modf(a0,frac,ent);
      return frac;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( modf_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_ < bd::arithmetic_<A0> >
                          )
  {
    using result_t = std::pair<A0,A0>;
    BOOST_FORCEINLINE result_t operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      A0 first, second;
      boost::simd::modf(a0, first, second);
      return {first, second};
    }
  };
  BOOST_DISPATCH_OVERLOAD ( modf_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_ < bd::arithmetic_<A0> >
                          , bd::scalar_ < bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &,  A0 a0, A0 & ent) const BOOST_NOEXCEPT
    {
      A0 frac;
      frac = std::modf(a0,&ent);
      return frac;
    }
  };

} } }


#endif
