//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_GTZ_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_GTZ_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-predicates
   This function object returns @ref True or @ref False according x is greater than @ref Zero or not.


    @par Header <boost/simd/function/is_gtz.hpp>

    @par Note

     Using `is_gtz(x)` is similar to: `x > 0`

    @par Example:

      @snippet is_gtz.cpp is_gtz

    @par Possible output:

      @snippet is_gtz.txt is_gtz

  **/
  as_logical_t<Value> is_gtz(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/is_gtz.hpp>
#include <boost/simd/function/simd/is_gtz.hpp>

#endif
