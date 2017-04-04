//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_CEIL_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_CEIL_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-arithmetic
    This function object computes the smallest integral representable value of
    its parameter type which is greater or equal to it.

    @par Header <boost/simd/function/ceil.hpp>

    @par Notes

     - @c ceil is also used as parameter to pass to @ref div or @ref rem

    @par Decorators

    - std_ for floating entries call std::ceil

    @see  floor, round, nearbyint, trunc, iceil

    @par Example:

      @snippet ceil.cpp ceil

    @par Possible output:

      @snippet ceil.txt ceil

  **/
  Value ceil(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/ceil.hpp>
#include <boost/simd/function/simd/ceil.hpp>

#endif
