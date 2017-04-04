//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_TWOPOWER_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_TWOPOWER_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-bitwise
    This function object returns \f$2^n\f$ (or 0 if n is less than zero)


    @par Header <boost/simd/function/twopower.hpp>

    @par Note:

    This function is not defined for floating entries

    @see  ilog2


    @par Example:

      @snippet twopower.cpp twopower

    @par Possible output:

      @snippet twopower.txt twopower

  **/
  IntegerValue twopower(IntegerValue const& x);
} }
#endif

#include <boost/simd/function/scalar/twopower.hpp>
#include <boost/simd/function/simd/twopower.hpp>

#endif
