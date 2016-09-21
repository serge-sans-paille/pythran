//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_NEGATE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_NEGATE_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-ieee
    Function object implementing negate capabilities

    Retuns the first element multiplied by the @ref sign of the second.

    @par Semantic:

    @code
    auto r = negate(x,y);
    @endcode

    is similar to:

    @code
    auto r =  x*sign(y);
    @endcode

    @par Note
    If y is @ref Zero the result is zero. This can be avoided using
    @ref negatenz or @ref copysign.

    @see sign, negatenz, copysign,  Mzero,  is_positive, is_negative

  **/
  Value negate(Value const & x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/negate.hpp>
#include <boost/simd/function/simd/negate.hpp>

#endif
