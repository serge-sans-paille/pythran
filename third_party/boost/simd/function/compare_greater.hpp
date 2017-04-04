//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_COMPARE_GREATER_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_COMPARE_GREATER_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-reduction
    This function object returns the return a @c bool that is the result of the
    lexicographic test for > on all elements of the entries

    It is probably not what you wish. Have a look to @ref is_greater


    @par Header <boost/simd/function/compare_greater.hpp>

    @par Example:

      @snippet compare_greater.cpp compare_greater

    @par Possible output:

      @snippet compare_greater.txt compare_greater

  **/
  bool compare_greater(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/compare_greater.hpp>
#include <boost/simd/function/simd/compare_greater.hpp>

#endif
