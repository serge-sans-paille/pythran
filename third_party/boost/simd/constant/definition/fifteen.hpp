//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_FIFTEEN_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_FIFTEEN_HPP_INCLUDED

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
    struct fifteen_ : boost::dispatch::constant_value_<fifteen_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,fifteen_,boost::dispatch::constant_value_<fifteen_>);
      BOOST_SIMD_REGISTER_CONSTANT(15,0x41700000U,0x402e000000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, fifteen_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::fifteen_,fifteen);
  }

  template<typename T> BOOST_FORCEINLINE auto Fifteen()
  BOOST_NOEXCEPT_DECLTYPE(detail::fifteen( boost::dispatch::as_<T>{}))
  {
    return detail::fifteen( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Fifteen(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Fifteen<T>())
  {
    return Fifteen<T>();
  }
} }

#endif
