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
    This function object returns a mask of bits. All ones if the
    argument is non @ref Zero else all zeros.
    This is an alias of @ref genmask



    @par Header <boost/simd/function/if_allbits_else_zero.hpp>

    @par Example:

      @snippet if_allbits_else_zero.cpp if_allbits_else_zero

    @par Possible output:

      @snippet if_allbits_else_zero.txt if_allbits_else_zero

  **/

  ///@{
  Value if_allbits_else_zero(Value const& x);
  as_arithmetic_t<LogicalValue> if_allbits_else_zero(LogicalValue const& x);
  ///@}
} }
#endif

#include <boost/simd/function/scalar/genmask.hpp>
#include <boost/simd/function/simd/if_allbits_else_zero.hpp>

#endif
