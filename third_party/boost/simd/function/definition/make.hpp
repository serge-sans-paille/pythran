//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DEFINITION_MAKE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DEFINITION_MAKE_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/as.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    BOOST_DISPATCH_MAKE_TAG(ext, make_, boost::dispatch::abstract_<make_>);
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, make_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::make_,make);
  }

  template<typename Target, typename Args> auto make(Args const& args)
  BOOST_NOEXCEPT_DECLTYPE(detail::make(as_<Target>(), args ))
  {
    return detail::make(as_<Target>(), args );
  }

  template<typename Target, typename... Args> auto make(Args const&... args)
  BOOST_NOEXCEPT_DECLTYPE(detail::make(as_<Target>(), args... ))
  {
    return detail::make(as_<Target>(), args... );
  }

  template<typename Target, typename... Args> auto make(Target const& tgt, Args const&... args)
  BOOST_NOEXCEPT_DECLTYPE(detail::make(tgt,args... ))
  {
    static_assert ( boost::dispatch::detail::is_target<Target>::value
                  , "boost::simd::make first parameter must be an instanciation of boost::simd::as_"
                  );

    return detail::make(tgt,args... );
  }
} }

#endif
