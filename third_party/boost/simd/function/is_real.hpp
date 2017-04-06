//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_REAL_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_REAL_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-predicates

    This function object returns @ref True or @ref False according x is real or not.
    For non complex numbers this is always true.


    @par Header <boost/simd/function/is_real.hpp>

    @par Note

     Using `is_real(x)` is similar to: `True` for real inputs.

    @par Example:

      @snippet is_real.cpp is_real

    @par Possible output:

      @snippet is_real.txt is_real

  **/
  as_logical_t<Value> is_real(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/is_real.hpp>
#include <boost/simd/function/scalar/is_real.hpp>
#include <boost/simd/function/simd/is_real.hpp>

#endif
