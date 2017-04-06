//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_LOG2_E_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_LOG2_E_HPP_INCLUDED

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
    struct log2_e_ : boost::dispatch::constant_value_<log2_e_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,log2_e_,boost::dispatch::constant_value_<log2_e_>);
      BOOST_SIMD_REGISTER_CONSTANT(1, 0x3fb8aa3bUL, 0x3FF71547652B82FEULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, log2_e_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::log2_e_,log2_e);
  }

  template<typename T> BOOST_FORCEINLINE auto Log2_e()
  BOOST_NOEXCEPT_DECLTYPE(detail::log2_e( boost::dispatch::as_<T>{}))
  {
    return detail::log2_e( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Log2_e(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Log2_e<T>())
  {
    return Log2_e<T>();
  }
} }

#endif
