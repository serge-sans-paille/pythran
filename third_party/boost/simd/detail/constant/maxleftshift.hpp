//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_MAXLEFTSHIFT_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_MAXLEFTSHIFT_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*

    @ingroup group-constant

    Generate the number of bits-1 of the scalar component of the value type

    @par Semantic:

    @code
    as_integer<T> r = Maxleftshift<T>();
    @endcode

    is similar to:

    @code
    as_integer<T> r =size(scalar_of<T>)*8-1;
    @endcode

    @return The Maxleftshift constant for the proper type
  */

namespace boost { namespace simd
{
  namespace tag
  {
    namespace tt = nsm::type_traits;

    struct maxleftshift_ : boost::dispatch::constant_value_<maxleftshift_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,maxleftshift_,boost::dispatch::constant_value_<maxleftshift_>);
      struct value_map
      {
        template<typename X>
        static tt::integral_constant<typename boost::dispatch::as_integer_t<X>,sizeof(X)*CHAR_BIT-1> value(boost::dispatch::arithmetic_<X> const&);
      };
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, maxleftshift_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::maxleftshift_,maxleftshift);
  }

  template<typename T> BOOST_FORCEINLINE auto Maxleftshift()
  BOOST_NOEXCEPT_DECLTYPE(detail::maxleftshift( boost::dispatch::as_<T>{}))
  {
    return detail::maxleftshift( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
