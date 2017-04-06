//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_CGOLD_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_CGOLD_HPP_INCLUDED

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
    struct cgold_ : boost::dispatch::constant_value_<cgold_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,cgold_,boost::dispatch::constant_value_<cgold_>);
      BOOST_SIMD_REGISTER_CONSTANT(0,0xbf1e377aUL,0xbfe3c6ef372fe950ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, cgold_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::cgold_,cgold);
  }

  template<typename T> BOOST_FORCEINLINE auto Cgold()
  BOOST_NOEXCEPT_DECLTYPE(detail::cgold( boost::dispatch::as_<T>{}))
  {
    return detail::cgold( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Cgold(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Cgold<T>())
  {
    return Cgold<T>();
  }
} }

#endif
