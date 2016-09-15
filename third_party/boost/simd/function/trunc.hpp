//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_TRUNC_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_TRUNC_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-arithmetic
    Function object implementing trunc capabilities

    Computes the truncation toward @ref Zero of its parameter.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = trunc(x);
    @endcode

    The code is similar to:

    @code
    T r = sign(x)*floor(abs(x));
    @endcode

    @par Note:

      - For floating point number it is also one of the two ouputs of
        the @ref modf function.
        And we have:
        @code
        trunc(x) + frac(x) == x;
        @endcode
        except for nans

      - If large numbers correct behaviour is not needed the fast_ decorator can be used,
        but 'fast_' means that no provisions are taken for floating values  too large to fit
         in the same size integer type.

    @par Alias:
    fix

    @par Decorators

    std_, fast_ for floating entries

    @see abs, frac, floor, sign, modf

  **/
  Value trunc(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/trunc.hpp>
#include <boost/simd/function/simd/trunc.hpp>

#endif
