//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_RROR_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_RROR_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-bitwise
    Function object implementing rror capabilities

    Returns the first entry rotated right or left
    by the absolute value of the second entry,
    according to its sign.

    @par semantic:
    For any given value @c x of type @c T, @c n  of type @c I:

    @code
    T r = rror(x, n);
    @endcode

    @par Note
    This function asserts if the integral parameter is out of range

    @see  ror, rrol, ror

  **/
  Value rror(Value const & x, IntegerValue const &n);
} }
#endif

#include <boost/simd/function/scalar/rror.hpp>
#include <boost/simd/function/simd/rror.hpp>

#endif
