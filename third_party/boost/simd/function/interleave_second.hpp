//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_INTERLEAVE_SECOND_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_INTERLEAVE_SECOND_HPP_INCLUDED

namespace boost { namespace simd
{
#if defined(DOXYGEN_ONLY)
  /*!

    @ingroup group-swar
    Function object implementing interleave_second capabilities

    Computes a vector from a combination of the two inputs.

    @par Semantic:

    For every parameters of type T:

    @code
    T r = interleave_second(x, y);
    @endcode

    is equivalent to :

    @code
    r = [ x[n/2-1] y[n/2-1] x[n/2] y[n/2] ... x[n-1] y[n-1] ]
    @endcode

    with <tt> n = cardinal_of<T>::value </tt>

  **/
  Value interleave_second(Value const& v0, Value const& v1);
#endif
} }

#include <boost/simd/function/simd/interleave_second.hpp>

#endif
