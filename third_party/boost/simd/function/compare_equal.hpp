//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_COMPARE_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_COMPARE_EQUAL_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-reduction
    Function object implementing compare_equal capabilities

    Returns a boolean that is the result of the lexicographic test for equality of all elements of
    the entries, i.e. return @ref true if and only if all corresponding entries elements are equal.

    @par Semantic:

    For every parameters of type T:

    @code
    auto r = compare_equal(x,y);
    @endcode

    is similar to:

    @code
    bool r = all(x == y);
    @endcode

    @see is_equal
  **/
  bool compare_equal(Value const& v0, Value const& v1);
} }
#endif

#include <boost/simd/function/scalar/compare_equal.hpp>
#include <boost/simd/function/simd/compare_equal.hpp>

#endif
