//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_COMPARE_NOT_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_COMPARE_NOT_EQUAL_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-reduction
    Function object implementing compare_not_equal capabilities

    Returns a logical scalar that is the result of the lexicographic
    test for != on elements of the entries,
    i.e. return @ref True if and only if two corresponding entries
    elements are not equal.

    It is probably not what you wish. Have a look to @ref is_not_equal

    @par Semantic:

    For every parameters of type T0:

    @code
    bool r = compare_not_equal(x,y);
    @endcode

    is similar to:

    @code
    bool r = any(x != y);
    @endcode

    @see is_not_equal
  **/
  bool compare_not_equal(Value const& v0, Value const& v1);
} }
#endif

#include <boost/simd/function/scalar/compare_not_equal.hpp>
#include <boost/simd/function/simd/compare_not_equal.hpp>

#endif
