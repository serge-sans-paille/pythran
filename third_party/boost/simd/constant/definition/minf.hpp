//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_MINF_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_MINF_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/constant/definition/valmin.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    struct minf_ : boost::dispatch::constant_value_<minf_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,minf_,boost::dispatch::constant_value_<minf_>);

      struct value_map
      {
        template<typename X>
        static auto value(X const& x) -> decltype(valmin_::value_map::value(x));

        template<typename X>
        static nsm::single_<0xFF800000U> value(boost::dispatch::single_<X> const&);

        template<typename X>
        static nsm::double_<0xFFF0000000000000ULL> value(boost::dispatch::double_<X> const&);
      };
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, minf_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::minf_,minf);
  }

  template<typename T> BOOST_FORCEINLINE auto Minf()
  -> decltype(detail::minf(boost::dispatch::as_<T>{}))
  {
    return detail::minf( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Minf(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Minf<T>())
  {
    return Minf<T>();
  }
} }

#endif

