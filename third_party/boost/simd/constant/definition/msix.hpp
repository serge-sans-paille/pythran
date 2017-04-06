//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_MSIX_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_MSIX_HPP_INCLUDED

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
    struct msix_ : boost::dispatch::constant_value_<msix_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,msix_,boost::dispatch::constant_value_<msix_>);
      BOOST_SIMD_REGISTER_CONSTANT(-6, 0xc0c00000UL, 0xc018000000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, msix_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::msix_,msix);
  }

  template<typename T> BOOST_FORCEINLINE auto Msix()
  BOOST_NOEXCEPT_DECLTYPE(detail::msix( boost::dispatch::as_<T>{}))
  {
    return detail::msix( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Msix(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Msix<T>())
  {
    return Msix<T>();
  }
} }

#endif
