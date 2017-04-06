//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_SPLITFACTOR_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_SPLITFACTOR_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*

    @ingroup group-constant

    Generate  a constant used to split a floating number in two parts,
    in floating point routines (such @ref two_add and
    @ref two_prod) to get extra precision.

    @par Semantic:

    @code
    T r = Splitfactor<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = 0
    else if T is double
      r =  pow(2, 27);
    else if T is float
      r =  pow(2, 13);
    @endcode

    @return The Splitfactor constant for the proper type
  */

namespace boost { namespace simd
{
  namespace tag
  {
    struct splitfactor_ : boost::dispatch::constant_value_<splitfactor_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,splitfactor_,boost::dispatch::constant_value_<splitfactor_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0x46000000UL, 0x41A0000000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, splitfactor_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::splitfactor_,splitfactor);
  }

  template<typename T> BOOST_FORCEINLINE auto Splitfactor()
  BOOST_NOEXCEPT_DECLTYPE(detail::splitfactor( boost::dispatch::as_<T>{}))
  {
    return detail::splitfactor( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
