//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_COMPARE_LESS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_COMPARE_LESS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-reduction
    This function object returns a @c bool that is the result of the
    lexicographic test for < on all elements of the entries

    It is probably not what you wish. Have a look to @ref is_less


    @par Header <boost/simd/function/compare_less.hpp>

    @par Example:

      @snippet compare_less.cpp compare_less

    @par Possible output:

      @snippet compare_less.txt compare_less

  **/
  bool compare_less(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/compare_less.hpp>
#include <boost/simd/function/simd/compare_less.hpp>

#endif
