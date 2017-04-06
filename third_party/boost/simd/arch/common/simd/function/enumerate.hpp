//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ENUMERATE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ENUMERATE_HPP_INCLUDED

#include <boost/simd/function/make.hpp>
#include <boost/simd/function/plus.hpp>
#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace simd { namespace ext
{
  // -----------------------------------------------------------------------------------------------
  // enumerate<T>()
  BOOST_DISPATCH_OVERLOAD( enumerate_
                          , (typename T, typename X)
                          , bd::cpu_
                          , bd::target_< bs::pack_< bd::fundamental_<T>, X > >
                          )
  {
    BOOST_FORCEINLINE typename T::type operator()(T const& ) const BOOST_NOEXCEPT
    {
      return do_( nsm::range<std::size_t,0,T::type::static_size>{} );
    }

    template<typename... N>
    static BOOST_FORCEINLINE typename T::type do_( nsm::list<N...> const& ) BOOST_NOEXCEPT
    {
      return make(as_<typename T::type>{}, N::value...);
    }
  };

  // -----------------------------------------------------------------------------------------------
  // enumerate<T>(x)
  BOOST_DISPATCH_OVERLOAD ( enumerate_
                          , (typename A0, typename T, typename X)
                          , bd::cpu_
                          , bd::scalar_< bd::fundamental_<A0> >
                          , bd::target_< bs::pack_< bd::fundamental_<T>, X > >
                          )
  {
    BOOST_FORCEINLINE typename T::type operator()(A0 a0, T const& ) const BOOST_NOEXCEPT
    {
      return a0 + enumerate<typename T::type>();
    }
  };

  // -----------------------------------------------------------------------------------------------
  // enumerate<T>(a,n)
  BOOST_DISPATCH_OVERLOAD( enumerate_
                          , (typename A0, typename A1,typename T,typename X)
                          , bd::cpu_
                          , bd::scalar_< bd::fundamental_<A0> >
                          , bd::scalar_< bd::fundamental_<A1> >
                          , bd::target_< bs::pack_< bd::fundamental_<T>, X > >
                          )
  {
    BOOST_FORCEINLINE typename T::type operator()(A0 a0, A1 a1, T const& ) const BOOST_NOEXCEPT
    {
      return a0 + a1*enumerate<typename T::type>();
    }
  };
} } }

#endif
