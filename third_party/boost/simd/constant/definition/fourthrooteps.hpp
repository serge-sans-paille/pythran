//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_FOURTHROOTEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_FOURTHROOTEPS_HPP_INCLUDED

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
    struct fourthrooteps_ : boost::dispatch::constant_value_<fourthrooteps_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,fourthrooteps_,boost::dispatch::constant_value_<fourthrooteps_>);
      BOOST_SIMD_REGISTER_CONSTANT(1, 0x3C9837F0,0x3F20000000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, fourthrooteps_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::fourthrooteps_,fourthrooteps);
  }

  template<typename T> BOOST_FORCEINLINE auto Fourthrooteps()
  BOOST_NOEXCEPT_DECLTYPE(detail::fourthrooteps( boost::dispatch::as_<T>{}))
  {
    return detail::fourthrooteps( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Fourthrooteps(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Fourthrooteps<T>())
  {
    return Fourthrooteps<T>();
  }
} }

#endif
