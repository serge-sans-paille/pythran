//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IF_ZERO_ELSE_ALLBITS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IF_ZERO_ELSE_ALLBITS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-boolean
    Function object implementing if_zero_else_allbits capabilities

    Returns a mask of bits. All ones if the
    input element is @ref Zero else all zeros.

    This is a convenience alias of @ref genmaskc
  **/
  Value if_zero_else_allbits(Value const& c);

  //@overload
  Value if_zero_else_allbits(LogicalValue const& c);
} }
#endif

#include <boost/simd/function/scalar/genmaskc.hpp>
#include <boost/simd/function/simd/if_zero_else_allbits.hpp>

#endif
