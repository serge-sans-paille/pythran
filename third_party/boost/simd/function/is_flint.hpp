//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_FLINT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_FLINT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-predicates
    This function object returns @ref True or @ref False according x is a flint or not.


    @par Header <boost/simd/function/is_flint.hpp>

    @par Note

    A flint is a 'floating integer' i.e. a floating number
    representing exactly an integer value.

    Be conscious that all sufficiently great floating points values
    are flint and even are even...

    @par Example:

      @snippet is_flint.cpp is_flint

    @par Possible output:

      @snippet is_flint.txt is_flint

  **/
  as_logical_t<Value> is_flint(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/is_flint.hpp>
#include <boost/simd/function/simd/is_flint.hpp>

#endif
