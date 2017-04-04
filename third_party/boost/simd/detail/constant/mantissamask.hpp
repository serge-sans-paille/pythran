//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_MANTISSAMASK_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_MANTISSAMASK_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*

    @ingroup group-constant

    Generate a mask used to compute the mantissa of a floating point value

    @par Semantic:

    @code
    as_integer<T> r = Mantissamask<T>();
    @endcode

    @code
    if T is double
      r =  -2.225073858507200889e-308;
    else if T is float
      r =  -1.1754942106924410755e-38;
    @endcode

    @return The Mantissamask constant for the proper type
  */

namespace boost { namespace simd
{
  namespace tag
  {
    struct mantissamask_ : boost::dispatch::constant_value_<mantissamask_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,mantissamask_,boost::dispatch::constant_value_<mantissamask_>);
      BOOST_SIMD_REGISTER_CONSTANT(0,0x807FFFFFUL,0x800FFFFFFFFFFFFFULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, mantissamask_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::mantissamask_,mantissamask);
  }

  template<typename T> BOOST_FORCEINLINE auto Mantissamask()
  BOOST_NOEXCEPT_DECLTYPE(detail::mantissamask( boost::dispatch::as_<T>{}))
  {
    return detail::mantissamask( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
