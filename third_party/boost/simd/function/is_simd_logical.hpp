//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_SIMD_LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_SIMD_LOGICAL_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-reduction

    returns @ref True if each vector elements have all bits or no bit set.


    @par Header <boost/simd/function/is_simd_logical.hpp>

    @par Note

     Using `is_simd_logical(x)` is similar to `all(logical_or(x == Allbits(as(x)), x == Zero(as(x))))`

  **/
  bool is_simd_logical(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/is_simd_logical.hpp>
#include <boost/simd/function/simd/is_simd_logical.hpp>

#endif
