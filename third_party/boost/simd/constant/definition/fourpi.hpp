//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_FOURPI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_FOURPI_HPP_INCLUDED

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
    struct fourpi_ : boost::dispatch::constant_value_<fourpi_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,fourpi_,boost::dispatch::constant_value_<fourpi_>);
      BOOST_SIMD_REGISTER_CONSTANT(12, 0X41490FDBUL, 0X402921FB54442D18ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, fourpi_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::fourpi_,fourpi);
  }

  template<typename T> BOOST_FORCEINLINE auto Fourpi()
  BOOST_NOEXCEPT_DECLTYPE(detail::fourpi( boost::dispatch::as_<T>{}))
  {
    return detail::fourpi( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Fourpi(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Fourpi<T>())
  {
    return Fourpi<T>();
  }
} }

#endif
