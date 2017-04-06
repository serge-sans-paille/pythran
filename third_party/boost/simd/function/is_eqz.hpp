//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_EQZ_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_EQZ_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-predicates
    This function object returns @ref True or @ref False according x is @ref Zero or not.


    @par Header <boost/simd/function/is_eqz.hpp>

    @par Note

      Using `is_eqz(x)` is equivalent to `x == 0`

    @see is_nez, is_lez, is_ltz

    @par Example:

      @snippet is_eqz.cpp is_eqz

    @par Possible output:

      @snippet is_eqz.txt is_eqz

  **/
  as_logical_t<Value> is_eqz(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/is_eqz.hpp>
#include <boost/simd/function/simd/is_eqz.hpp>

#endif
