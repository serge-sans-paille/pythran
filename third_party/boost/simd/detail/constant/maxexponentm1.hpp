//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_MAXEXPONENTM1_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_MAXEXPONENTM1_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*

    @ingroup group-constant

    Generate the maximum exponent of floating point numbers minus one

    @par Semantic:

    @code
    as_integer<T> r = Maxexponentm1<T>();
    @endcode

    @code
    if T is double
      r =  1022;
    else if T is float
      r =  126;
    @endcode

    @return The Maxexponentm1 constant for the proper type
  */

namespace boost { namespace simd
{
  namespace tag
  {
    namespace tt = nsm::type_traits;
    struct maxexponentm1_ : boost::dispatch::constant_value_<maxexponentm1_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,maxexponentm1_,boost::dispatch::constant_value_<maxexponentm1_>);
      struct value_map
      {
        template<typename X>
        static tt::integral_constant<X,0> value(boost::dispatch::integer_<X> const&);

        template<typename X>
        static tt::integral_constant<std::int32_t,126> value(boost::dispatch::single_<X> const&);

        template<typename X>
        static tt::integral_constant<std::int64_t,1022> value(boost::dispatch::double_<X> const&);
      };
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, maxexponentm1_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::maxexponentm1_,maxexponentm1);
  }

  template<typename T> BOOST_FORCEINLINE auto Maxexponentm1()
  BOOST_NOEXCEPT_DECLTYPE(detail::maxexponentm1( boost::dispatch::as_<T>{}))
  {
    return detail::maxexponentm1( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
