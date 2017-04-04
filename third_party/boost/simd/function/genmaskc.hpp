//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_GENMASKC_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_GENMASKC_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-bitwise
    This function object returns a mask of bits. This mask is full of ones if the
    input element is @ref Zero else full of zeros.

    @par Header <boost/simd/function/genmaskc.hpp>

    @see genmask

    @par Example:

      @snippet genmaskc.cpp genmaskc

    @par Possible output:

      @snippet genmaskc.txt genmaskc

    @par Alias:
    @c if_zero_else_allbits

    @see if_else_allbits

  **/
  Value genmaskc(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/genmaskc.hpp>
#include <boost/simd/function/simd/genmaskc.hpp>

#endif
