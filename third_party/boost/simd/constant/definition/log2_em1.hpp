//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_LOG2_EM1_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_LOG2_EM1_HPP_INCLUDED

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
    struct log2_em1_ : boost::dispatch::constant_value_<log2_em1_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,log2_em1_,boost::dispatch::constant_value_<log2_em1_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0x3ee2a8edUL, 0x3fdc551d94ae0bf8ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, log2_em1_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::log2_em1_,log2_em1);
  }

  template<typename T> BOOST_FORCEINLINE auto Log2_em1()
  BOOST_NOEXCEPT_DECLTYPE(detail::log2_em1( boost::dispatch::as_<T>{}))
  {
    return detail::log2_em1( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Log2_em1(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Log2_em1<T>())
  {
    return Log2_em1<T>();
  }
} }

#endif
