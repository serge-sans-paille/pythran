//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_FNMS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_FNMS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-arithmetic
    This function object computes the negated (fused) multiply substract of
    its three parameters.


    @par Header <boost/simd/function/fnms.hpp>

    @par Notes
    The call `fnms(x, y, z)` is similar to `-x*y+z`

    But really conformant fused multiply/add also implies

    - only one rounding

    - no "intermediate" overflow

    fnms provides this for all integral types and also each time it is reasonable
    in terms of performance for floating ones (i.e. if the system has the hard
    wired capability).

    If you need pedantic fnms capabilities in all circumstances in your own
    code you can use the pedantic_ decorator (can be very expensive).

    @par Decorators
    - pedantic_ ensures the fnms properties and allows SIMD acceleration if available.

    @see fms, fma, fnma

    @par Example:

      @snippet fnms.cpp fnms

    @par Possible output:

      @snippet fnms.txt fnms

  **/
  Value fnms(Value const& x, Value const& y, Value const& z);
} }
#endif

#include <boost/simd/function/scalar/fnms.hpp>
#include <boost/simd/function/simd/fnms.hpp>

#endif
