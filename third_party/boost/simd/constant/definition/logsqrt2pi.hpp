//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_LOGSQRT2PI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_LOGSQRT2PI_HPP_INCLUDED

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
    struct logsqrt2pi_ : boost::dispatch::constant_value_<logsqrt2pi_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,logsqrt2pi_,boost::dispatch::constant_value_<logsqrt2pi_>);
      BOOST_SIMD_REGISTER_CONSTANT( 1, 0x3f6b3f8eUL, 0x3fed67f1c864beb5ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, logsqrt2pi_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::logsqrt2pi_,logsqrt2pi);
  }

  template<typename T> BOOST_FORCEINLINE auto Logsqrt2pi()
  BOOST_NOEXCEPT_DECLTYPE(detail::logsqrt2pi( boost::dispatch::as_<T>{}))
  {
    return detail::logsqrt2pi( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Logsqrt2pi(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Logsqrt2pi<T>())
  {
    return Logsqrt2pi<T>();
  }
} }

#endif
