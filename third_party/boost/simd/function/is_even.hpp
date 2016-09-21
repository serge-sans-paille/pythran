//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_EVEN_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_EVEN_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-predicates
    Function object implementing is_even capabilities

    Returns @ref True or @ref False according x is even or not.

    @par Semantic:

    @code
    auto r = is_even(x);
    @endcode

    is similar to:

    @code
    auto r = to_int(x/2)*2 == x;
    @endcode

    @par Note:

    A floating number is even if it is a  flint
    and divided by two it is still a flint.

    A flint is a 'floating integer' i.e. a floating number
    representing an integer value

    Be conscious that all sufficiently great floating points values are even...

    @see is_odd, is_flint

  **/
  as_logical_t<Value> is_even(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/is_even.hpp>
#include <boost/simd/function/simd/is_even.hpp>

#endif
