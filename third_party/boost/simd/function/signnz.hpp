//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SIGNNZ_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SIGNNZ_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-ieee
    This function object returns the sign of x. I.e. -1 or 1,
    depending on the fact  @c x is negative or positive.

    @par Header <boost/simd/function/signnz.hpp>
    @par Notes:

    - This function never returns @ref Zero (zero is considered positive for integers).

    - For floating point numbers the bit of sign is taken into account and so
    we always have `signnz(-z) == -signnz(z)` except is the entry is a NaN
    (in this later case the result is undefined).


    @see Mzero, sign, is_negative, is_positive

    @par Example:

      @snippet signnz.cpp signnz

    @par Possible output:

      @snippet signnz.txt signnz

  **/
  Value signnz(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/signnz.hpp>
#include <boost/simd/function/simd/signnz.hpp>

#endif
