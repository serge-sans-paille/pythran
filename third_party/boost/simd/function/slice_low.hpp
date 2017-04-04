//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SLICE_LOW_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SLICE_LOW_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-swar
    Type-preserving pack lower slicing

    This function object returns the lower slice of a simd::pack, i.e a simd::pack of same type
    containing the lower half of ts argument.


    @par Header <boost/simd/function/slice_low.hpp>

    @par Semantic:

    For any value @c a of type @c T and cardinal @c N, the following code:

    @code
    pack<T,N/2> c = slice_low(a);
    @endcode

    is equivalent to

    @code
    pack<T,N/2> c( a[0], ..., a[N/2-1]);
    @endcode

    @see slice, slice_high, combine
  **/
  ValueO slice_low(Value1 const& x);
} }
#endif

#include <boost/simd/function/simd/slice_low.hpp>

#endif
