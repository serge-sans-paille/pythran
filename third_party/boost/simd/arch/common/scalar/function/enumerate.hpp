//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ENUMERATE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ENUMERATE_HPP_INCLUDED

#include <boost/simd/constant/zero.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  // -----------------------------------------------------------------------------------------------
  // enumerate<T>()
  BOOST_DISPATCH_OVERLOAD ( enumerate_
                          , (typename T)
                          , bd::cpu_
                          , bd::target_< bd::scalar_< bd::unspecified_<T> > >
                          )
  {
    BOOST_FORCEINLINE typename T::type operator()(T const& ) const BOOST_NOEXCEPT
    {
      return Zero<typename T::type>();
    }
  };

  // -----------------------------------------------------------------------------------------------
  // enumerate<T>(x)
  BOOST_DISPATCH_OVERLOAD ( enumerate_
                          , (typename A0, typename T)
                          , bd::cpu_
                          , bd::scalar_< bd::unspecified_<A0> >
                          , bd::target_< bd::scalar_< bd::unspecified_<T> > >
                          )
  {
    BOOST_FORCEINLINE typename T::type operator()( A0 const& a0, T const& ) const BOOST_NOEXCEPT
    {
      return static_cast<typename T::type>(a0);
    }
  };

  // -----------------------------------------------------------------------------------------------
  // enumerate<T>(a,n)
  BOOST_DISPATCH_OVERLOAD ( enumerate_
                          , (typename A0, typename A1,typename T)
                          , bd::cpu_
                          , bd::scalar_< bd::unspecified_<A0> >
                          , bd::scalar_< bd::unspecified_<A1> >
                          , bd::target_< bd::scalar_< bd::unspecified_<T> > >
                          )
  {
    BOOST_FORCEINLINE
    typename T::type operator()( A0 const& a0, A1 const&, T const& ) const BOOST_NOEXCEPT
    {
      return static_cast<typename T::type>(a0);
    }
  };
} } }

#endif
