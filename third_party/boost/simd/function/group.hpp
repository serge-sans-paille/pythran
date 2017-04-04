//==================================================================================================
/*!
  @file
    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_GROUP_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_GROUP_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-swar
    This function object aggregates two boost::simd::pack of basic type @c T and cardinal @c N into
    a single boost::simd::pack of cardinal @c 2*N and using a type twice smaller than @c T.

    Conversion of values during this operations are made using the C language conversion rules and
    may induce roll over.


    @par Header <boost/simd/function/group.hpp>

    @par Semantic:
    For any type @c T and integral constant @c N, consider two value @c x and @c y of type
    @c boost::simd::pack<T,N>. The following code:
    @code
    auto r = group(x, y);
    @endcode
    is equivalent to:
    @code
    boost::simd::downgrade_t< boost::simd::pack<T,N> >  r{x[0], ..., x[N-1], y[0], ..., y[N-1]};
    @endcode

    @param x First pack to aggregate
    @param y Second pack to aggregate
    @return The aggregation of all values in its arguments, converted to the downgraded type.
  **/
  downgrade_t<Value> group(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/simd/group.hpp>

#endif
