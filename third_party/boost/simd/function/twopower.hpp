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
    Function object implementing twopower capabilities

    Returns \f$2^n\f$ (or 0 if n is less than zero)

    @par semantic:
    For any given value @c n  of integral type @c N:

    @code
    N r = twopower(n);
    @endcode

    code is similar to:

    @code
    N r = 1 << n;
    @endcode

    @par Note:

    This function is not defined for floating entries

    @see  ilog2

  **/
  Value twopower(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/twopower.hpp>
#include <boost/simd/function/simd/twopower.hpp>

#endif
