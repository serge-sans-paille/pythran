//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_MAXFLINT_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_MAXFLINT_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*

    @ingroup group-constant

    Generate the least integer value which is exactly
    representable in floating point numbers and
    equal to its integral successor.

    All floating numbers greater than Maxflint are integral.

    @par Semantic:

    @code
    T r = Maxflint<T>();
    @endcode

    is similar to:

    @code
    if T is double
      r = 9007199254740992.0
    else if T is float
      r = 16777216.0f
    @endcode


    @return The Maxflint constant for the proper type
  */

namespace boost { namespace simd
{
  namespace tag
  {
    struct maxflint_ : boost::dispatch::constant_value_<maxflint_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,maxflint_,boost::dispatch::constant_value_<maxflint_>);
      BOOST_SIMD_REGISTER_CONSTANT(1, 0x4b800000, 0x4340000000000000ll);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, maxflint_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::maxflint_,maxflint);
  }

  template<typename T> BOOST_FORCEINLINE auto Maxflint()
  BOOST_NOEXCEPT_DECLTYPE(detail::maxflint( boost::dispatch::as_<T>{}))
  {
    return detail::maxflint( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
