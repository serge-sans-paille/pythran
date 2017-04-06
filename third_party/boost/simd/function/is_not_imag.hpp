//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_NOT_IMAG_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_NOT_IMAG_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-predicates

    This function object returns @ref True or @ref False according x is not pure imaginary or is.

    For non complex numbers it is @ref True except if x is @ref Zero.


    @par Header <boost/simd/function/is_not_imag.hpp>

    @par Note

     Using `is_not_imag(x)` is similar to: `x != 0` for real entries.

    @par Example:

      @snippet is_not_imag.cpp is_not_imag

    @par Possible output:

      @snippet is_not_imag.txt is_not_imag

  **/
  as_logical_t<Value> is_not_imag(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/is_not_imag.hpp>
#include <boost/simd/function/scalar/is_not_imag.hpp>
#include <boost/simd/function/simd/is_not_imag.hpp>

#endif
