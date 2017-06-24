//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_NBDIGITS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_NBDIGITS_HPP_INCLUDED

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
    namespace tt = nsm::type_traits;

    struct nbdigits_ : boost::dispatch::constant_value_<nbdigits_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,nbdigits_,boost::dispatch::constant_value_<nbdigits_>);

      struct value_map
      {
        template<typename X>
        static tt::integral_constant<X,0> value(boost::dispatch::integer_<X> const&);

        template<typename X>
        static tt::integral_constant<std::int32_t,24> value(boost::dispatch::single_<X> const&);

        template<typename X>
       static tt::integral_constant<std::int64_t,53> value(boost::dispatch::double_<X> const&);
      };
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, nbdigits_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::nbdigits_,nbdigits);
  }

  template<typename T> BOOST_FORCEINLINE auto Nbdigits()
  BOOST_NOEXCEPT_DECLTYPE(detail::nbdigits( boost::dispatch::as_<T>{}))
  {
    return detail::nbdigits( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Nbdigits(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Nbdigits<T>())
  {
    return Nbdigits<T>();
  }
} }

#endif
