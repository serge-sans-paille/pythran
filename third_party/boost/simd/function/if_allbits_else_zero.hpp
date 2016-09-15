//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IF_ALLBITS_ELSE_ZERO_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IF_ALLBITS_ELSE_ZERO_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-boolean
    Function object implementing if_allbits_else_zero capabilities

    Returns a mask of bits. All ones if the
    input element is non @ref Zero else all zeros.

    This is a convenience alias of @ref genmask
  **/
  Value if_allbits_else_zero(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/genmask.hpp>
#include <boost/simd/function/simd/if_allbits_else_zero.hpp>

#endif
