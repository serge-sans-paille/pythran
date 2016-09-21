//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_C180_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_C180_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/brigand.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*

    @ingroup group-constant

    Generate the value 180 in the chosen type

    @code
    T r = C180<T>();
    @endcode

    is similar to

    @code
    T r = T(180);
    @endcode

    @return The C180 constant for the proper type
  */

namespace boost { namespace simd
{
  namespace tag
  {
    struct c180_ : boost::dispatch::constant_value_<c180_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,c180_,boost::dispatch::constant_value_<c180_>);
      BOOST_SIMD_REGISTER_CONSTANT(180, 0x43340000UL, 0x4066800000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag,c180_);
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::c180_,c180);
  }

  template<typename T> BOOST_FORCEINLINE auto C180()
  BOOST_NOEXCEPT_DECLTYPE(detail::c180( boost::dispatch::as_<T>{}))
  {
    return detail::c180( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
