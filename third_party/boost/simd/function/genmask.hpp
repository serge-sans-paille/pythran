//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_GENMASK_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_GENMASK_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-bitwise
    This function object returns a mask of bits. This mask is full of ones if the
    input element is non @ref Zero else full of zeros.

    @see genmaskc

    @par Header <boost/simd/function/genmask.hpp>

    @par Example:

      @snippet genmask.cpp genmask

    @par Possible output:

      @snippet genmask.txt genmask

    @par Alias:
    @c if_allbits_else_zero

    @see if_allbits_else

  **/

  ///@{
  as_arithmetic_t<LogicalValue> genmask(const LogicalValue& a);
  Value genmask(const Value& a);
  ///@}
} }
#endif

#include <boost/simd/function/scalar/genmask.hpp>
#include <boost/simd/function/simd/genmask.hpp>

#endif
