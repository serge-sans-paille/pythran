//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_EXP_1_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_EXP_1_HPP_INCLUDED

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
    struct exp_1_ : boost::dispatch::constant_value_<exp_1_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,exp_1_,boost::dispatch::constant_value_<exp_1_>);
      BOOST_SIMD_REGISTER_CONSTANT(3, 0x402df854UL, 0x4005bf0a8b145769uLL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, exp_1_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::exp_1_,exp_1);
  }

  template<typename T> BOOST_FORCEINLINE auto Exp_1()
  BOOST_NOEXCEPT_DECLTYPE(detail::exp_1( boost::dispatch::as_<T>{}))
  {
    return detail::exp_1( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Exp_1(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Exp_1<T>())
  {
    return Exp_1<T>();
  }
} }

#endif
