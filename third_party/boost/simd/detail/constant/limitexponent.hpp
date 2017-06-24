//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_LIMITEXPONENT_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_LIMITEXPONENT_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*

    @ingroup group-constant

    Generate the limit exponent of floating point numbers,  that is Maxexponant+1

    @par Semantic:

    @code
    as_integer<T> r = Limitexponent<T>();
    @endcode

    @code
    if T is double
      r =  1024;
    else if T is float
      r =  128;
    @endcode

    @return The Limitexponent constant for the proper type
  */

namespace boost { namespace simd
{
  namespace tag
  {
    namespace tt = nsm::type_traits;

    struct limitexponent_ : boost::dispatch::constant_value_<limitexponent_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,limitexponent_,boost::dispatch::constant_value_<limitexponent_>);

      struct value_map
      {
        template<typename X>
        static tt::integral_constant<X,0> value(boost::dispatch::integer_<X> const&);

        template<typename X>
        static tt::integral_constant<std::int32_t,128> value(boost::dispatch::single_<X> const&);

        template<typename X>
        static tt::integral_constant<std::int64_t,1024> value(boost::dispatch::double_<X> const&);
      };
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, limitexponent_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::limitexponent_,limitexponent);
  }

  template<typename T> BOOST_FORCEINLINE auto Limitexponent()
  BOOST_NOEXCEPT_DECLTYPE(detail::limitexponent( boost::dispatch::as_<T>{}))
  {
    return detail::limitexponent( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
