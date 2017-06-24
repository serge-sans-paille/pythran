//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_MASK1FREXP_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_MASK1FREXP_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*

    @ingroup group-constant

    Generate the constant mask1frexp,  a utility mask for frexp implementation.

    @par Semantic:

    @code
    as_integer<T> r = Mask1frexp<T>();
    @endcode

    @code
    if T is double
      r =  9218868437227405312l;
    else if T is float
      r =  2139095040;
    @endcode

    @return The Mask1frexp constant for the proper type
  */

namespace boost { namespace simd
{
  namespace tag
  {
    namespace tt = nsm::type_traits;

    struct mask1frexp_ : boost::dispatch::constant_value_<mask1frexp_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,mask1frexp_,boost::dispatch::constant_value_<mask1frexp_>);

      struct value_map
      {
        template<typename X>
        static tt::integral_constant<X,0> value(boost::dispatch::integer_<X> const&);

        template<typename X>
        static tt::integral_constant<std::int32_t,0x7F800000L> value(boost::dispatch::single_<X> const&);

        template<typename X>
        static tt::integral_constant<std::int64_t,0x7FF0000000000000LL> value(boost::dispatch::double_<X> const&);
      };
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, mask1frexp_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::mask1frexp_,mask1frexp);
  }

  template<typename T> BOOST_FORCEINLINE auto Mask1frexp()
  BOOST_NOEXCEPT_DECLTYPE(detail::mask1frexp( boost::dispatch::as_<T>{}))
  {
    return detail::mask1frexp( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
