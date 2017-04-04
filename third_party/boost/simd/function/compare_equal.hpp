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
    This function object returns `all(x == y)`,
    i.e. return @c true if and only if all corresponding entries elements are equal.


    @par Header <boost/simd/function/compare_equal.hpp>

    @par Example:

      @snippet compare_equal.cpp compare_equal

    @par Possible output:

      @snippet compare_equal.txt compare_equal

  **/
  bool compare_equal(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/compare_equal.hpp>
#include <boost/simd/function/simd/compare_equal.hpp>

#endif
