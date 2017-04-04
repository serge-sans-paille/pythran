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
    This function object returns the sign of @c x. i.e. -1, 0 or 1,
    depending on the fact  @c x is less than @ref Zero, @ref Zero or
    greater than @ref Zero.

    For floating,  the sign of @ref Nan is @ref Nan,
    the sign of @ref Mzero is also @ref Zero.

    @see signnz, is_negative, is_positive,  bitofsign



    @par Header <boost/simd/function/sign.hpp>

    @par Example:

      @snippet sign.cpp sign

    @par Possible output:

      @snippet sign.txt sign

  **/
  Value sign(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/sign.hpp>
#include <boost/simd/function/simd/sign.hpp>

#endif
