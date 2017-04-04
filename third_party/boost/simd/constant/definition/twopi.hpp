//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_TWOPI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_TWOPI_HPP_INCLUDED

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
    struct twopi_ : boost::dispatch::constant_value_<twopi_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,twopi_,boost::dispatch::constant_value_<twopi_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0X40C90FDB, 0X401921FB54442D18LL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, twopi_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::twopi_,twopi);
  }

  template<typename T> BOOST_FORCEINLINE auto Twopi()
  BOOST_NOEXCEPT_DECLTYPE(detail::twopi( boost::dispatch::as_<T>{}))
  {
    return detail::twopi( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Twopi(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Twopi<T>())
  {
    return Twopi<T>();
  }
} }

#endif
