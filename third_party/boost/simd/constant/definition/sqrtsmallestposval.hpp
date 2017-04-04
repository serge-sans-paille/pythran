//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_SQRTSMALLESTPOSVAL_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_SQRTSMALLESTPOSVAL_HPP_INCLUDED

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
    struct sqrtsmallestposval_ : boost::dispatch::constant_value_<sqrtsmallestposval_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,sqrtsmallestposval_,boost::dispatch::constant_value_<sqrtsmallestposval_>);
      BOOST_SIMD_REGISTER_CONSTANT( 1, 0x20000000UL, 0x2000000000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, sqrtsmallestposval_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::sqrtsmallestposval_,sqrtsmallestposval);
  }

  template<typename T> BOOST_FORCEINLINE auto Sqrtsmallestposval()
  BOOST_NOEXCEPT_DECLTYPE(detail::sqrtsmallestposval( boost::dispatch::as_<T>{}))
  {
    return detail::sqrtsmallestposval( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Sqrtsmallestposval(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Sqrtsmallestposval<T>())
  {
    return Sqrtsmallestposval<T>();
  }
} }

#endif
