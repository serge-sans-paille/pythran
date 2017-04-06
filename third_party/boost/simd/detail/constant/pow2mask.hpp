//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_POW2MASK_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_POW2MASK_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*

    @ingroup group-constant

    Generate a mask value used in pow2

    @return The Pow2mask constant for the proper type
  */

namespace boost { namespace simd
{
  namespace tag
  {
    struct pow2mask_ : boost::dispatch::constant_value_<pow2mask_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,pow2mask_,boost::dispatch::constant_value_<pow2mask_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0x7FBFFFUL, 0xFFEFFFFFFFFFFULL);
    };
  }
      //    mask is  ~bitwise_or(Minf<A0>(), iA0(siA0(1) <<  (Nbmantissabits<sA0>()-Nbexponentbits<sA0>()-1)))
      //    if it is needed for other floating type

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag,pow2mask_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::pow2mask_,pow2mask);
  }

  template<typename T> BOOST_FORCEINLINE auto Pow2mask()
  BOOST_NOEXCEPT_DECLTYPE(detail::pow2mask( boost::dispatch::as_<T>{}))
  {
    return detail::pow2mask( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
