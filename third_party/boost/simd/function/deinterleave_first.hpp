//==================================================================================================
/*!
  @file
    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DEINTERLEAVE_FIRST_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DEINTERLEAVE_FIRST_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
/*!
    @ingroup group-swar
    This function object performs the extraction of the first part of a boost::simd::pack
    containing two channels of data.


    @par Header <boost/simd/function/deinterleave_first.hpp>

    @par Semantic:
    For any type @c T and any integral constant @c N greater than 1, let's consider two values @c x
    and @c y of type @c boost::simd::pack<T,N> , the following code:
    @code
    boost::simd::pack<T,N> r = deinterleave_first(x,y);
    @endcode
    is equivalent to :
    @code
    boost::simd::pack<T,N> r{x[0], x[2], ..., x[N/2], y[0], y[2], ...,y[N/2]};
    @endcode

    @param  x  First part of the data to deinterleave
    @param  y  Second part of the data to deinterleave
    @return A boost::simd::pack containing the deinterleaved value of the first data channel.
  **/
  Value deinterleave_first(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/simd/deinterleave_first.hpp>

#endif
