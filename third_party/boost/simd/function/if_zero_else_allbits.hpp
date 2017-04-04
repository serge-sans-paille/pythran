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
    This function object conditionally returns  @c 0 (respectively @ref Allbits)
    if @c c is @ref True (respectively  @ref False)

    This is an alias of @ref genmaskc



    @par Header <boost/simd/function/if_zero_else_allbits.hpp>

    @par Example:

      @snippet if_zero_else_allbits.cpp if_zero_else_allbits

    @par Possible output:

      @snippet if_zero_else_allbits.txt if_zero_else_allbits

  **/

  ///@{
  as_arithmetic_t<LogicalValue> if_zero_else_allbits(LogicalValue const& c);
  Value if_zero_else_allbits(Value const& c);
  ///@}
} }
#endif

#include <boost/simd/function/scalar/genmaskc.hpp>
#include <boost/simd/function/simd/if_zero_else_allbits.hpp>

#endif
