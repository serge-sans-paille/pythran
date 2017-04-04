//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_SQRTEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_SQRTEPS_HPP_INCLUDED

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
    struct sqrteps_ : boost::dispatch::constant_value_<sqrteps_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,sqrteps_,boost::dispatch::constant_value_<sqrteps_>);
      BOOST_SIMD_REGISTER_CONSTANT(1, 0x39B504F3UL, 0x3E50000000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, sqrteps_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::sqrteps_,sqrteps);
  }

  template<typename T> BOOST_FORCEINLINE auto Sqrteps()
  BOOST_NOEXCEPT_DECLTYPE(detail::sqrteps( boost::dispatch::as_<T>{}))
  {
    return detail::sqrteps( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Sqrteps(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Sqrteps<T>())
  {
    return Sqrteps<T>();
  }
} }

#endif
