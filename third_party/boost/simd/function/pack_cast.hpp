//==================================================================================================
/*!
  @file

  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_PACK_CAST_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_PACK_CAST_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-bitwise

    This function objects converts the elements of its argument to an arbitrary type

    @c Target while preserving its argument's cardinal.

    @tparam Target @c Target type to cast toward

    @par Header <boost/simd/function/pack_cast.hpp>

    @param x Value to cast

    @return A value of type @c Target which is cast to @c x.
  **/
  template<typename Target, typename Value>
  Target pack_cast(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/pack_cast.hpp>
#include <boost/simd/function/simd/pack_cast.hpp>

#endif
