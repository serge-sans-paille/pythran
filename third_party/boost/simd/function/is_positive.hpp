//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_POSITIVE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_POSITIVE_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-predicates

    This function object returns @ref True if x is positive else @ref False.

    This function differs from @ref is_gtz for floating point arguments,
    because @ref Zero is positive but not greater than 0, and @ref Mzero is
    not positive and not greater than 0, It's probably @ref is_gtz that
    you want.


    @par Header <boost/simd/function/is_positive.hpp>

    @par Note

     Using `is_positive(x)` is similar to `bitofsign(x) == 0`
     for signed types and is always true for unsigned ones.

    @par Example:

      @snippet is_positive.cpp is_positive

    @par Possible output:

      @snippet is_positive.txt is_positive

  **/
  as_logical_t<Value> is_positive(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/is_positive.hpp>
#include <boost/simd/function/simd/is_positive.hpp>

#endif
