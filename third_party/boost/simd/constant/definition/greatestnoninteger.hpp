//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_GREATESTNONINTEGER_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_GREATESTNONINTEGER_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/brigand.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    struct greatestnoninteger_ : boost::dispatch::constant_value_<greatestnoninteger_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,greatestnoninteger_,boost::dispatch::constant_value_<greatestnoninteger_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0x4affffffLL, 0x432fffffffffffffULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag,greatestnoninteger_);
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::greatestnoninteger_,greatestnoninteger);
  }

  template<typename T> BOOST_FORCEINLINE auto Greatestnoninteger()
  BOOST_NOEXCEPT_DECLTYPE(detail::greatestnoninteger( boost::dispatch::as_<T>{}))
  {
    return detail::greatestnoninteger( boost::dispatch::as_<T>{} );
  }
} }

#endif
