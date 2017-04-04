//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_HYPOT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_HYPOT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-arithmetic
    This function object computes the hypothenuse length: \f$(x^2 + y^2)^{1/2}\f$


    @par Header <boost/simd/function/hypot.hpp>

    @par Decorators

     - pedantic_ with this decorator provisions are made to avoid overflow
       and to compute  @c hypot as accurately as possible in any cases.

     - std_ call std::hypot

    @see sqr, sqrt

    @par Example:

      @snippet hypot.cpp hypot

    @par Possible output:

      @snippet hypot.txt hypot


  **/
  IEEEValue hypot(IEEEValue const& x, IEEEValue const& y);
} }
#endif

#include <boost/simd/function/scalar/hypot.hpp>
#include <boost/simd/function/scalar/hypot.hpp>
#include <boost/simd/function/simd/hypot.hpp>

#endif
