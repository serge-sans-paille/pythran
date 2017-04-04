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
    This function object returns @c true if and only if two corresponding entries
    elements are not equal.

    It is probably not what you wish. Have a look to @ref is_not_equal

    @par Header <boost/simd/function/compare_not_equal.hpp>

    @par Example:

      @snippet compare_not_equal.cpp compare_not_equal

    @par Possible output:

      @snippet compare_not_equal.txt compare_not_equal

  **/
  bool compare_not_equal(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/compare_not_equal.hpp>
#include <boost/simd/function/simd/compare_not_equal.hpp>

#endif
