//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_VALMIN_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_VALMIN_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    namespace tt = nsm::type_traits;

    struct valmin_ : boost::dispatch::constant_value_<valmin_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,valmin_,boost::dispatch::constant_value_<valmin_>);

      struct value_map
      {
        template<typename X>
        static tt::integral_constant<X,-128> value(boost::dispatch::int8_<X> const&);

        template<typename X>
        static tt::integral_constant<X,-32768> value(boost::dispatch::int16_<X> const&);

        template<typename X>
        static tt::integral_constant<X,-2147483647-1> value(boost::dispatch::int32_<X> const&);

        template<typename X>
        static tt::integral_constant<X,-9223372036854775807LL -1LL> value(boost::dispatch::int64_<X> const&);

        template<typename X>
        static tt::integral_constant<X,X(0)> value(boost::dispatch::uint_<X> const&);

        template<typename X>
        static nsm::single_<0xFF7FFFFF> value(boost::dispatch::single_<X> const&);

        template<typename X>
        static nsm::double_<0xFFEFFFFFFFFFFFFFULL> value(boost::dispatch::double_<X> const&);
      };
    };
  }


  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, valmin_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::valmin_,valmin);
  }

  template<typename T> BOOST_FORCEINLINE auto Valmin()
  -> decltype(detail::valmin(boost::dispatch::as_<T>{}))
  {
    return detail::valmin( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Valmin(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Valmin<T>())
  {
    return Valmin<T>();
  }
} }

#endif

