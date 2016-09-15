//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SLICE_HIGH_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SLICE_HIGH_HPP_INCLUDED

namespace boost { namespace simd
{
#if defined(DOXYGEN_ONLY)
  /*!
    @ingroup group-swar
    Type-preserving pack higher slicing

    This function object returns the lower slice of a simd::pack, i.e a simd::pack of same type
    containing the higher half of ts argument.

    @par Semantic:

    For any value @c a of type @c T and cardinal @c N, the following code:

    @code
    pack<T,N/2> c = slice_high(a);
    @endcode

    is equivalent to

    @code
    pack<T,N/2> c( a[N/2], ..., a[N-1]);
    @endcode

    @see slice
    @see slice_low
    @see combine
  **/
  ValueO2 slice_high(Value const & x);
#endif
} }

#include <boost/simd/function/simd/slice_high.hpp>

#endif
