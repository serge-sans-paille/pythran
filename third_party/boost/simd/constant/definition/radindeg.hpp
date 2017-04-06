//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_RADINDEG_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_RADINDEG_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    struct radindeg_ : boost::dispatch::constant_value_<radindeg_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,radindeg_,boost::dispatch::constant_value_<radindeg_>);
      BOOST_SIMD_REGISTER_CONSTANT(57, 0X42652EE1, 0X404CA5DC1A63C1F8LL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, radindeg_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::radindeg_,radindeg);
  }

  template<typename T> BOOST_FORCEINLINE auto Radindeg()
  BOOST_NOEXCEPT_DECLTYPE(detail::radindeg( boost::dispatch::as_<T>{}))
  {
    return detail::radindeg( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Radindeg(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Radindeg<T>())
  {
    return Radindeg<T>();
  }
} }

#endif
