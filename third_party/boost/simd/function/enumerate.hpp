//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ENUMERATE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ENUMERATE_HPP_INCLUDED

namespace boost { namespace simd
{
#if defined(DOXYGEN_ONLY)
  /*!
    @ingroup group-swar
    Generates a value containing sequentially increasing elements, starting with @c seed and
    repetitively evaluating @c seed+=step.


    @par Header <boost/simd/function/enumerate.hpp>

    @par SIMD Semantic:
    For any type @c T and integral constant @c N, the following code:
    @code
    auto r = enumerate<boost::simd::pack<T,N>>(seed, step);
    @endcode
    is equivalent to:
    @code
    boost::simd::pack<T,N> r{seed, seed+step, ..., seed+(N-1)*step};
    @endcode

    @param seed Initial value of store, equals to @c 0 by default.
    @param step Increment to apply on each subsequent generated value, equals to @c 1 by default.
    @return A value containing the sequence of value generated from @c seed and @c step
  **/
  Value enumerate(const ScalarValue& seed = 0, const ScalarValue& step = 1);
#endif
} }

#include <boost/simd/function/scalar/enumerate.hpp>
#include <boost/simd/function/simd/enumerate.hpp>

#endif
