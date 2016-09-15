//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ROR_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ROR_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-bitwise
    Function object implementing ror capabilities

    Returns the first entry rotated right
    by the value of the second entry.

    @par semantic:
    For any given value @c x of type @c T, @c n  of type @c I:

    @code
    T r = ror(x, n);
    @endcode

    @par Note
    This function asserts if the integral parameter is out of range

    @see  rol, rror, rrol

  **/
  Value ror(Value const & v0, IntegerValue const& n);
} }
#endif

#include <boost/simd/function/scalar/ror.hpp>
#include <boost/simd/function/simd/ror.hpp>

#endif
