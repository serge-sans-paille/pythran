//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_LOGPI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_LOGPI_HPP_INCLUDED

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
    struct logpi_ : boost::dispatch::constant_value_<logpi_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,logpi_,boost::dispatch::constant_value_<logpi_>);
      BOOST_SIMD_REGISTER_CONSTANT(1, 0x3f928682UL, 0x3ff250d048e7a1bdULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, logpi_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::logpi_,logpi);
  }

  template<typename T> BOOST_FORCEINLINE auto Logpi()
  BOOST_NOEXCEPT_DECLTYPE(detail::logpi( boost::dispatch::as_<T>{}))
  {
    return detail::logpi( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Logpi(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Logpi<T>())
  {
    return Logpi<T>();
  }
} }

#endif
