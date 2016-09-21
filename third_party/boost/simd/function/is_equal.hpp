//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_EQUAL_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-operator
    Function object implementing is_equal capabilities

    Returns @ref True or @ref False
    according x and y are equal or not.

    Infix notation can be used with operator '=='

    @par Semantic:

    @code
    auto r = is_equal(x,y);
    @endcode

    or

    @code
    auto r = x == y;
    @endcode

    @see  is_not_equal, is_eqz, is_equal_with_equal_nans

  **/
  as_logical_t<T0> is_equal(T0 const& x, T1 const& y);
} }
#endif

#include <boost/simd/function/scalar/is_equal.hpp>
#include <boost/simd/function/simd/is_equal.hpp>

#endif
