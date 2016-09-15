//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SIGN_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SIGN_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-ieee
    Function object implementing sign capabilities

    Returns the sign of x. i.e. -1, 0 or 1, according
    x is less than @ref Zero, @ref Zero or greater than @ref Zero.

    For floating,  the sign of @ref Nan is @ref Nan,
    the sign of @ref Mzero is also @ref Zero.

    @par Semantic:

    @code
    auto r = sign(x);
    @endcode

    @see signnz, is_negative, is_positive,  bitofsign

  **/
  Value sign(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/sign.hpp>
#include <boost/simd/function/simd/sign.hpp>

#endif
