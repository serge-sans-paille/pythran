//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_DEGINRAD_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_DEGINRAD_HPP_INCLUDED

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
    struct deginrad_ : boost::dispatch::constant_value_<deginrad_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,deginrad_,boost::dispatch::constant_value_<deginrad_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0X3C8EFA35, 0X3F91DF46A2529D39LL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, deginrad_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::deginrad_,deginrad);
  }

  template<typename T> BOOST_FORCEINLINE auto Deginrad()
  BOOST_NOEXCEPT_DECLTYPE(detail::deginrad( boost::dispatch::as_<T>{}))
  {
    return detail::deginrad( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Deginrad(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Deginrad<T>())
  {
    return Deginrad<T>();
  }
} }

#endif
