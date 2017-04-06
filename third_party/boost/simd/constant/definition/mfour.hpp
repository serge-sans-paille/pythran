//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_MFOUR_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_MFOUR_HPP_INCLUDED

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
    struct mfour_ : boost::dispatch::constant_value_<mfour_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,mfour_,boost::dispatch::constant_value_<mfour_>);
      BOOST_SIMD_REGISTER_CONSTANT(-4, 0xc0800000UL, 0xc010000000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, mfour_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::mfour_,mfour);
  }

  template<typename T> BOOST_FORCEINLINE auto Mfour()
  BOOST_NOEXCEPT_DECLTYPE(detail::mfour( boost::dispatch::as_<T>{}))
  {
    return detail::mfour( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Mfour(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Mfour<T>())
  {
    return Mfour<T>();
  }
} }

#endif
