//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_TWO_PROD_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_TWO_PROD_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-arithmetic
    This function object computes two reals of the type of the inputs
    (in an std::pair)  @c r0 and @c r1 such that:

    @code
    r0 = x * y
    r1 = r0 -(x * y)
    @endcode

    using perfect arithmetic.

    Its main usage is to be able to compute
    prod of reals and the residual error using IEEE 754 arithmetic.


    @par Header <boost/simd/function/two_prod.hpp>

    @par Example:

      @snippet two_prod.cpp two_prod

    @par Possible output:

      @snippet two_prod.txt two_prod


  **/
  std::pair<Value, Value> two_prod(Value const& x, Value const& y);

} }
#endif

#include <boost/simd/function/scalar/two_prod.hpp>
#include <boost/simd/function/simd/two_prod.hpp>

#endif
