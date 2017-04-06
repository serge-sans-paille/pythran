//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_MSEVEN_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_MSEVEN_HPP_INCLUDED

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
    struct mseven_ : boost::dispatch::constant_value_<mseven_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,mseven_,boost::dispatch::constant_value_<mseven_>);
      BOOST_SIMD_REGISTER_CONSTANT(-7, 0xc0e00000UL, 0xc01c000000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, mseven_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::mseven_,mseven);
  }

  template<typename T> BOOST_FORCEINLINE auto Mseven()
  BOOST_NOEXCEPT_DECLTYPE(detail::mseven( boost::dispatch::as_<T>{}))
  {
    return detail::mseven( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Mseven(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Mseven<T>())
  {
    return Mseven<T>();
  }
} }

#endif
