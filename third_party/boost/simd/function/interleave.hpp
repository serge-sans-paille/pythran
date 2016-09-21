//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_INTERLEAVE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_INTERLEAVE_HPP_INCLUDED

namespace boost { namespace simd
{

#if defined(DOXYGEN_ONLY)
  /*!
    @ingroup group-swar
    Function object implementing interleave capabilities

    Evaluates the two interleaved data extracted from its arguments
    while minimizing redundant computations.

    @par Semantic:

    For every parameters @c x and @c y of type @c T :
    @code
    std::array<T,2> r = interleave(x,y);
    @endcode

    is equivalent to :

    @code
    std::array<T,2> r = { interleave_first(x,y), interleave_second(x,y) };
    @endcode
  **/
  std::array<Value,2> interleave(Value const& v0, Value const& v1);
#endif
} }

#include <boost/simd/function/simd/interleave.hpp>

#endif
