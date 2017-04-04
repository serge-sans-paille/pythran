//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_FIX_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_FIX_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-arithmetic
    This function object computes the truncation toward @ref Zero
    of its parameter.

    @par Header <boost/simd/function/fix.hpp>

    It is an alias of @ref trunc

    @see ceil, floor, round,  nearbyint, trunc, ifix, itrunc

    @par Example:

      @snippet fix.cpp fix

    @par Possible output:

      @snippet fix.txt fix

  **/
  Value fix(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/trunc.hpp>
#include <boost/simd/function/simd/fix.hpp>

#endif
