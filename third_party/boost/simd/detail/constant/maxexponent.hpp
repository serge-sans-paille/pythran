//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_MAXEXPONENT_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_MAXEXPONENT_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*

    @ingroup group-constant

    Generate the maximum exponent of floating point numbers

    @par Semantic:

    @code
    as_integer<T> r = Maxexponent<T>();
    @endcode

    @code
    if T is double
      r =  1023;
    else if T is float
      r =  127;
    @endcode

    @return The Maxexponent constant for the proper type
  */

namespace boost { namespace simd
{
  namespace tag
  { 
    namespace tt = nsm::type_traits;
     struct value_map
      {
        template<typename X>
        static tt::integral_constant<X,0> value(boost::dispatch::integer_<X> const&);

        template<typename X>
        static tt::integral_constant<std::int32_t,128> value(boost::dispatch::single_<X> const&);

        template<typename X>
        static tt::integral_constant<std::int64_t,1024> value(boost::dispatch::double_<X> const&);
      };
    struct maxexponent_ : boost::dispatch::constant_value_<maxexponent_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,maxexponent_,boost::dispatch::constant_value_<maxexponent_>);
      struct value_map
      {
        template<typename X>
        static tt::integral_constant<X,0> value(boost::dispatch::integer_<X> const&);

        template<typename X>
        static tt::integral_constant<std::int32_t,127> value(boost::dispatch::single_<X> const&);

        template<typename X>
        static tt::integral_constant<std::int64_t,1023> value(boost::dispatch::double_<X> const&);
      };
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, maxexponent_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::maxexponent_,maxexponent);
  }

  template<typename T> BOOST_FORCEINLINE auto Maxexponent()
  BOOST_NOEXCEPT_DECLTYPE(detail::maxexponent( boost::dispatch::as_<T>{}))
  {
    return detail::maxexponent( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
