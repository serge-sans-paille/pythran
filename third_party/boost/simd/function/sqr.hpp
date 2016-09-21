//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SQR_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SQR_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-arithmetic
    Function object implementing sqr capabilities

    Computes the square of its parameter.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = sqr(x);
    @endcode

    is equivalent to:

    @code
    T r = x*x;
    @endcode

  **/
  Value sqr(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/sqr.hpp>
#include <boost/simd/function/simd/sqr.hpp>

#endif
