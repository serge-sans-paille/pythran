//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_THIRDROOTEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_THIRDROOTEPS_HPP_INCLUDED

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
    struct thirdrooteps_ : boost::dispatch::constant_value_<thirdrooteps_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,thirdrooteps_,boost::dispatch::constant_value_<thirdrooteps_>);
      BOOST_SIMD_REGISTER_CONSTANT( 1, 0x3BA14518UL, 0X3ED965FEA53D6E3DULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, thirdrooteps_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::thirdrooteps_,thirdrooteps);
  }

  template<typename T> BOOST_FORCEINLINE auto Thirdrooteps()
  BOOST_NOEXCEPT_DECLTYPE(detail::thirdrooteps( boost::dispatch::as_<T>{}))
  {
    return detail::thirdrooteps( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Thirdrooteps(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Thirdrooteps<T>())
  {
    return Thirdrooteps<T>();
  }
} }

#endif
