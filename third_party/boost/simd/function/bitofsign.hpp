//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_BITOFSIGN_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_BITOFSIGN_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-ieee
    Function object implementing bitofsign capabilities

    Returns a value of the same type as the input with all bits set to zero
    except the bit of sign which is preserved.

    Returns always @ref Zero for unsigned types

    @par Semantic:

    @code
    auto r = bitofsign(x);
    @endcode

    for signed types is similar to:

    @code
    auto r = x&Signmask<T>();
    @endcode

    @see sign, signnz, is_negative, is_positive, Mzero, Signmask;

  **/
  Value bitofsign(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/bitofsign.hpp>
#include <boost/simd/function/simd/bitofsign.hpp>

#endif
