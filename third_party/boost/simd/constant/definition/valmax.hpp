//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_VALMAX_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_VALMAX_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/detail/dispatch/meta/as_unsigned.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>
#include <climits>

namespace boost { namespace simd
{
  namespace tag
  {
    namespace tt = nsm::type_traits;

    struct valmax_ : boost::dispatch::constant_value_<valmax_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,valmax_,boost::dispatch::constant_value_<valmax_>);

      struct value_map
      {
        template<typename X>
        static tt::integral_constant<X,0x7F> value(boost::dispatch::int8_<X> const&);

        template<typename X>
        static tt::integral_constant<X,0x7FFF> value(boost::dispatch::int16_<X> const&);

        template<typename X>
        static tt::integral_constant<X,0x7FFFFFFF> value(boost::dispatch::int32_<X> const&);

        template<typename X>
        static tt::integral_constant<X,0x7FFFFFFFFFFFFFFF> value(boost::dispatch::int64_<X> const&);

        template<typename X>
        static tt::integral_constant<X,X(0xFFFFFFFFFFFFFFFFULL)> value(boost::dispatch::uint_<X> const&);

        template<typename X>
        static nsm::single_<0x7F7FFFFF> value(boost::dispatch::single_<X> const&);

        template<typename X>
        static nsm::double_<0x7FEFFFFFFFFFFFFFULL> value(boost::dispatch::double_<X> const&);
      };
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, valmax_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::valmax_,valmax);
  }

  template<typename T> BOOST_FORCEINLINE auto Valmax()
  -> decltype(detail::valmax(boost::dispatch::as_<T>{}))
  {
    return detail::valmax( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Valmax(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Valmax<T>())
  {
    return Valmax<T>();
  }
} }

#endif
