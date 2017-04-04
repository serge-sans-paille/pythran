//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_LOG10_PI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_LOG10_PI_HPP_INCLUDED

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
    struct log10_pi_ : boost::dispatch::constant_value_<log10_pi_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,log10_pi_,boost::dispatch::constant_value_<log10_pi_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0x3efe8a6eU, 0x3fdfd14db31ba3bbULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, log10_pi_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::log10_pi_,log10_pi);
  }

  template<typename T> BOOST_FORCEINLINE auto Log10_pi()
  BOOST_NOEXCEPT_DECLTYPE(detail::log10_pi( boost::dispatch::as_<T>{}))
  {
    return detail::log10_pi( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Log10_pi(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Log10_pi<T>())
  {
    return Log10_pi<T>();
  }
} }

#endif
