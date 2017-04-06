//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_NOT_REAL_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_NOT_REAL_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-predicates

    This function object returns @ref True or @ref False according x is real or not.
    For non complex numbers it is always false


    @par Header <boost/simd/function/is_not_real.hpp>

    @par Note

     Using `is_not_real(x)` is similar to: `False` for real inputs.

    @par Example:

      @snippet is_not_real.cpp is_not_real

    @par Possible output:

      @snippet is_not_real.txt is_not_real

  **/
  as_logical_t<Value> is_not_real(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/is_not_real.hpp>
#include <boost/simd/function/scalar/is_not_real.hpp>
#include <boost/simd/function/simd/is_not_real.hpp>

#endif
