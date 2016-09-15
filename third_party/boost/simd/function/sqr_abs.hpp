//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SQR_ABS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SQR_ABS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-arithmetic
    Function object implementing sqr_abs capabilities

    Computes the square of the absolute value of its parameter. For real entries it is the same as @ref sqr.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = sqr_abs(x);
    @endcode

    is equivalent to:

    @code
    T r = sqr(abs(x));
    @endcode

  **/
  Value sqr_abs(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/sqr_abs.hpp>
#include <boost/simd/function/simd/sqr_abs.hpp>

#endif
