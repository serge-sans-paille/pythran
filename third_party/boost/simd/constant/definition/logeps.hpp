//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_LOGEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_LOGEPS_HPP_INCLUDED

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
    struct logeps_ : boost::dispatch::constant_value_<logeps_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,logeps_,boost::dispatch::constant_value_<logeps_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0xc17f1402UL, 0xc04205966f2b4f12ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, logeps_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::logeps_,logeps);
  }

  template<typename T> BOOST_FORCEINLINE auto Logeps()
  BOOST_NOEXCEPT_DECLTYPE(detail::logeps( boost::dispatch::as_<T>{}))
  {
    return detail::logeps( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Logeps(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Logeps<T>())
  {
    return Logeps<T>();
  }
} }

#endif
